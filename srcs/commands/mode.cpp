/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:13:09 by thoberth          #+#    #+#             */
/*   Updated: 2022/04/05 17:46:32 by thoberth         ###   ########.fr       */
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
 * s - marks a user for receipt of server notices.
 * 
 * The flag 'a' SHALL NOT be toggled by the user using the MODE command,
 * instead use of the AWAY command is REQUIRED
 * 
 * user cannot make themselves an operator but they can use -o -0
 * 
 * @param user 
 * @param content 
 */
void	user_mode(t_data &data, Users &client, std::string content)
{
	bool	to_add_or_rm = true;
	unsigned long	pos;
	if (content.find('-') == 0)
		to_add_or_rm = false;
	if ((pos = content.find("r")) != std::string::npos || \
		(pos = content.find("O")) != std::string::npos || \
		(pos = content.find("o")) != std::string::npos || \
		(pos = content.find("w")) != std::string::npos || \
		(pos = content.find("i")) != std::string::npos)
	{
		if (to_add_or_rm)
		{
			if (client.getMode().find(content[pos]) == std::string::npos)
				client.setMode(client.getMode() + content[pos]);
			if (content[0] == '+')
				user_mode(data, client, content.erase(pos, 1));
			else
				user_mode(data, client, content.erase(pos, 1));
		}
		else
		{
			if ((pos = client.getMode().find(content[pos])) != std::string::npos)
			{
				std::string tmp = client.getMode();
				client.setMode(tmp.erase(pos, 1));
				user_mode(data, client, content.erase(pos, 1));
			}
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
	if (pos > pos2)
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
	if (args[1].find('-') == 0)
		to_add_or_rm = false;
	if ((pos = args[1].find("k")) != std::string::npos || \
		(pos = args[1].find("l")) != std::string::npos || \
		(pos = args[1].find("O")) != std::string::npos || \
		(pos = args[1].find("o")) != std::string::npos || \
		(pos = args[1].find("b")) != std::string::npos)
	{
		if (to_add_or_rm)
		{
			if (chan.getMode().find(args[1][pos]) == std::string::npos)
				chan.setMode(chan.getMode() + args[1][pos]);
			args[1].erase(pos, 1);
			chan_mode(data, chan, sender, args);
		}
		else
		{
			if ((pos = chan.getMode().find(args[1][pos])) != std::string::npos)
			{
				std::string tmp = chan.getMode();
				chan.setMode(tmp.erase(pos, 1));
				args[1].erase(pos, 1);
				chan_mode(data, chan, sender, args);
			}
		}
	}
	else
		send_packets(sender, create_reply(data, &sender, 324, chan_modeis_arg(chan)));
}
