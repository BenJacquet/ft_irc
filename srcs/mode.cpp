/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:13:09 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/28 13:20:31 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief 
 * <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
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
 * <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
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

	for(size_t i=2; i < args.size(); i++)
		content += args[i] + " " ;
	if (((new_chan = is_chan_exist(data, args[1])) != NULL) ||
		(new_usr = find_client_nick(data, args[1])) != data.users.end())
	{
		if (new_chan)
			chan_mode(*new_chan, content);
		else
		{
			user_mode(*new_usr, content);
		}
	}
	else
		CERR(RED, "User or Channel " << args[1] << "not found\n");
}

/**
 * @brief @to_add_or_rm is true if added, false if deletion flag
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
	if ((pos = content.find("iwoOr")) != std::string::npos)
	{
		if (to_add_or_rm)
		{
			if (user.getMode().find(content[pos]) == std::string::npos)
				user.setMode(user.getMode() + content[pos]);
			if (content[0] == '+')
				user_mode(user, content.erase(0, pos + 1));
			else
				user_mode(user, content.erase(0, pos));
		}
		else
		{
			if (user.getMode().find(content[pos]) != std::string::npos)
			{
				std::string tmp = user.getMode();
				user.setMode(tmp.erase(pos, 1));
				user_mode(user, content.erase(0, pos + 1));
			}
		}
	}
}


void	chan_mode(Chan &chan, std::string content)
{
	(void)chan;
	(void)content;
}
