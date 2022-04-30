/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:13:09 by thoberth          #+#    #+#             */
/*   Updated: 2022/04/30 16:10:44 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

/**
 * @brief 
 * 
 * @param data 
 * @param cmd 
 */
void	mode_parsing(t_data &data, Message &cmd)
{
	replace_user(data, *cmd.getSender());
	Chan	*new_chan;
	v_Users::iterator	new_usr;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args.size() == 1)
	{
		send_packets(*cmd.getSender(), create_reply(data, cmd.getSender(), 461, args[0]));
		return ;
	}
	std::string content;
	for(size_t i=2; i <= args.size() - 1; i++)
		content += args[i] + " " ;
	if (((new_chan = is_chan_exist(data, args[1])) != NULL) ||
		(new_usr = find_client_nick(data, args[1])) != data.users.end())
	{
		if (new_chan)
			chan_mode(data, *new_chan, *cmd.getSender(), args);
		else
			user_mode(data, *new_usr, content);
	}
	else
		CERR(RED, "User or Channel " << args[1] << " not found\n");
}

/**
 * @brief @to_add_or_rm is true if added, false if deletion flag
 * * <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
 * a - user is flagged as away;
 * i - marks a users as invisible;
 * w - user receives wallops;
 * r - restricted user connection;
 * o - operator flag;
 * O - local operator flag;
 * 
 * The flag 'a' SHALL NOT be toggled by the user using the MODE command,
 * instead use of the AWAY command is REQUIRED
 * 
 * user cannot make themselves an operator but they can use -o -O
 * 
 * @param user 
 * @param content 
 */
void	user_mode(t_data &data, Users &client, std::string content)
{
	bool	to_add_or_rm = true;
	unsigned long	pos;
	unsigned long	pos2;
	if (content.find('-') == 0)
		to_add_or_rm = false;
	if ((pos = content.find("O")) != std::string::npos || \
		(pos = content.find("o")) != std::string::npos || \
		(pos = content.find("w")) != std::string::npos || \
		(pos = content.find("i")) != std::string::npos)
	{
		if (to_add_or_rm && (client.getMode().find(&content[pos]) == std::string::npos))
		{
			if (client.getMode().find(content[pos]) == std::string::npos && \
				content[pos] != 'o' && content[pos] != 'O')
				client.setMode(client.getMode() + content[pos]);
			send_packets(client, RPL_MODE(client.getNick_name(), "+" + content[pos]));
			user_mode(data, client, content.erase(pos, 1));
		}
		else
		{
			if ((pos2 = client.getMode().find(content[pos])) != std::string::npos)
			{
				send_packets(client, RPL_MODE(client.getNick_name(), "-" + content[pos]));
				std::string tmp = client.getMode();
				content.erase(pos, 1);
				client.setMode(tmp.erase(pos2, 1));
				user_mode(data, client, content);
			}
			else
				send_packets(client, create_reply(data, &client, 221, ""));
		}
	}
	else
		send_packets(client, create_reply(data, &client, 221, ""));
}

std::string		chan_modeis_arg(Chan &chan)
{
	std::string ret = chan.getName() + " " + chan.getMode();
	unsigned long pos = -1;
	unsigned long pos2 = -1;
	pos = chan.getMode().find("l");
	pos2 = chan.getMode().find("k");
	if (pos < pos2)
	{
		if (pos != std::string::npos)
			ret += " " + chan.getLimit_user();
		if (pos2 != std::string::npos)
			ret += " " + chan.getPw();
	}
	else
	{
		if (pos2 != std::string::npos)
			ret += " " + chan.getPw();
		if (pos != std::string::npos)
			ret += " " + chan.getLimit_user();
	}
	return ret;
}

bool	lk_parsing(t_data &data, Chan &chan, Users &sender, std::vector<std::string> &args, int pos)
{
	if (args.size() <= 3)
	{
		send_packets(sender, create_reply(data, &sender, 461, args[0]));
		return false;
	}
	else if (args[2][pos] == 'k' && chan.getMode().find("k") != std::string::npos)
	{
		send_packets(sender, create_reply(data, &sender, 467, chan.getName()));
		return false;
	}
	else
	{
		if (args[2][pos] == 'l')
			chan.setLimit_user(args[3]);
		else
			chan.setPw(args[3]);
		args.erase(args.begin() + 3);
	}
	return true;
}

bool	ban_mode(t_data &data, Chan &chan, Users &sender, std::vector<std::string> &args)
{
	size_t pos;
	if (args.size() > 3)
	{
		std::string target_nick;
		Users *target;
		if ((pos = args[3].find(",")) != std::string::npos)
		{
			target_nick.assign(args[3], 0, pos);
			args[3].erase(0, pos + 1);
		}
		else
			target_nick = args[3];
		target = &(*find_client_nick(data, target_nick));
		v_Users vectu = chan.getUsers();
		v_Users::iterator it = vectu.begin();
		for (v_Users::iterator ite = vectu.end();
			 it != ite && *it != *target; it++)
			;
		if (it == vectu.end())
		{
			send_packets(sender, create_reply(data, &sender, 441, target_nick + " " + chan.getName()));
			return false;
		}
		chan.add_toBlacklist(*target);
		it = vectu.begin();
		for (v_Users::iterator ite = vectu.end(); it != ite; it++)
			send_packets(*it, ":" + it->getFull_id() + " " + RPL_BAN(target->getNick_name(), chan.getName()));
	}
	else
	{
		v_Users vect = chan.getBlacklist();
		if (vect.size() > 0)
		{
			std::string content = chan.getName() + " :";
			for (v_Users::iterator it = vect.begin(),
								   ite = vect.end();
				 it != ite; it++)
				content += " " + it->getNick_name();
			send_packets(sender, create_reply(data, &sender, 367, content));
		}
		send_packets(sender, create_reply(data, &sender, 368, chan.getName()));
	}
	return true;
}

bool unban_mode(t_data &data, Chan &chan, Users &sender, std::vector<std::string> &args)
{
	size_t pos;
	if (args.size() > 3)
	{
		std::string target_nick;
		Users *target;
		if ((pos = args[3].find(",")) != std::string::npos)
		{
			target_nick.assign(args[3], 0, pos);
			args[3].erase(0, pos + 1);
		}
		else
			target_nick = args[3];
		target = &(*find_client_nick(data, target_nick));
		v_Users vectu = chan.getUsers();
		v_Users::iterator it = vectu.begin();
		for (v_Users::iterator ite = vectu.end();
			 it != ite && *it != *target; it++)
			;
		if (it == vectu.end())
		{
			send_packets(sender, create_reply(data, &sender, 441, target_nick + " " + chan.getName()));
			return false;
		}
		chan.rm_toBlacklist(*target);
		it = vectu.begin();
		for (v_Users::iterator ite = vectu.end(); it != ite; it++)
			send_packets(*it, ":" + it->getFull_id() + " " + RPL_UNBAN(target->getNick_name(), chan.getName()));
	}
	else
	{
		send_packets(sender, create_reply(data, &sender, 461, args[0]));
		return false;
	}
	return true;
}

/**
 * @brief 
 * * <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
 * k - Sets a key on channel
 * l - limit user count
 * 0 - give/take channel creator status
 * o - give/take channel operator privilege
 * b - set/remove ban mask to keep users out
 * @param chan 
 * @param content 
 */
void	chan_mode(t_data &data, Chan &chan, Users &sender, std::vector<std::string> args)
{
	bool	to_add_or_rm = true;
	unsigned long	pos;
	if (args.size() <= 2)
	{
		send_packets(sender, create_reply(data, &sender, 324, chan_modeis_arg(chan)));
		return ;
	}
	if (sender != chan.getCreator() && sender.getMode().find_first_of("oO") == std::string::npos)
	{
		send_packets(sender, create_reply(data, &sender, 482, chan.getName()));
		return ;
	}
	if (args[2].find('-') == 0)
		to_add_or_rm = false;
	if ((pos = args[2].find("k")) != std::string::npos || \
		(pos = args[2].find("l")) != std::string::npos || \
		(pos = args[2].find("b")) != std::string::npos)
	{
		if (to_add_or_rm)
		{
			if (args[2][pos] == 'k' || args[2][pos] == 'l')
			{
				if (!(lk_parsing(data, chan, sender, args, pos)))
					return ;
			}
			if (args[2][pos] == 'b')
			{
				if (!(ban_mode(data, chan, sender, args)))
					return ;
			}
			if (chan.getMode().find(args[2][pos]) == std::string::npos && args[2][pos] != 'b')
			{
				chan.setMode(chan.getMode() + args[2][pos]);
				args[2].erase(pos, 1);
				chan_mode(data, chan, sender, args);
			}
		}
		else
		{
			if (args[2][pos] == 'b')
			{
				if (!(unban_mode(data, chan, sender, args)))
					return ;
			}
			if ((pos = chan.getMode().find(args[2][pos])) != std::string::npos)
			{
				std::string tmp = chan.getMode();
				chan.setMode(tmp.erase(pos, 1));
				args[2].erase(pos, 1);
				chan_mode(data, chan, sender, args);
			}
		}
	}
	else
		send_packets(sender, create_reply(data, &sender, 324, chan_modeis_arg(chan)));
}
