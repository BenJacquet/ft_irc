/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:13:09 by thoberth          #+#    #+#             */
/*   Updated: 2022/04/01 17:29:15 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief 
 * 
 * @param data 
 * @param cmd 
 */
void	mode_parsing(t_data &data, Message &cmd)
{
	Chan	*new_chan;
	v_Users::iterator	new_usr;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	std::string content;

	replace_user(data, *cmd.getSender());

	for(size_t i=2; i <= args.size() - 1; i++)
		content += args[i] + " " ;
	if (((new_chan = is_chan_exist(data, args[1])) != NULL) ||
		(new_usr = find_client_nick(data, args[1])) != data.users.end())
	{
		if (new_chan)
		{
			chan_mode(*new_chan, content);
			COUT(L_MAGENTA, new_chan->getTopic() << " mode is " << new_chan->getMode());
		}
		else
		{
			user_mode(*new_usr, content);
			COUT(L_MAGENTA, new_usr->getNick_name() << " mode is " << new_usr->getMode());
		}
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
void	user_mode(Users &user, std::string content)
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
			if (user.getMode().find(content[pos]) == std::string::npos)
				user.setMode(user.getMode() + content[pos]);
			if (content[0] == '+')
				user_mode(user, content.erase(pos, 1));
			else
				user_mode(user, content.erase(pos, 1));
		}
		else
		{
			if ((pos = user.getMode().find(content[pos])) != std::string::npos)
			{
				std::string tmp = user.getMode();
				user.setMode(tmp.erase(pos, 1));
				user_mode(user, content.erase(pos, 1));
			}
		}
	}
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
void	chan_mode(Chan &chan, std::string content)
{
	bool	to_add_or_rm = true;
	unsigned long	pos;
	if (content.find('-') == 0)
		to_add_or_rm = false;
	if ((pos = content.find("k")) != std::string::npos || \
		(pos = content.find("l")) != std::string::npos || \
		(pos = content.find("O")) != std::string::npos || \
		(pos = content.find("o")) != std::string::npos || \
		(pos = content.find("b")) != std::string::npos)
	{
		if (to_add_or_rm)
		{
			if (chan.getMode().find(content[pos]) == std::string::npos)
				chan.setMode(chan.getMode() + content[pos]);
			if (content[0] == '+')
				chan_mode(chan, content.erase(pos, 1));
			else
				chan_mode(chan, content.erase(pos, 1));
		}
		else
		{
			if ((pos = chan.getMode().find(content[pos])) != std::string::npos)
			{
				std::string tmp = chan.getMode();
				chan.setMode(tmp.erase(pos, 1));
				chan_mode(chan, content.erase(pos, 1));
			}
		}
	}
}
