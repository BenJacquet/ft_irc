/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:50:41 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/21 11:00:03 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	command_privmsg(t_data &data, Message &cmd)
{
	Chan	*new_chan;
	d_Users::iterator	new_usr;
	std::vector<std::string> args = parse_line(std::string(cmd.getPayload()));
	if (args.size() == 1)
	{
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 461) + ERR_NEEDMOREPARAMS(args[0]));
		return ;
	}
	std::string content;
	for(size_t i=2; i < args.size(); i++)
		content += args[i] + " " ;
	if (((new_chan = is_chan_exist(data, args[1])) != NULL) ||
		(new_usr = find_client_nick(data, args[1])) != data.users.end())
	{
		if (new_chan != NULL)
		{
			if (new_chan->is_banned(cmd.getSender()) || !(new_chan->is_in_channel(cmd.getSender())))
			{
				send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 404) + ERR_CANNOTSENDTOCHAN(new_chan->getName()));
				return ;
			}
			channel_privmsg(*new_chan, *cmd.getSender(), content);
		}
		else
		{
			if (new_usr->getMode().find("a") != std::string::npos)
				send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 301) +
				RPL_AWAY(new_usr->getNick_name() + " :" + new_usr->getAway_mode()));
			else {
				content = ":" + cmd.getSender()->getFull_id() + " PRIVMSG " +\
				new_usr->getNick_name() + " " + content;
				send_packets(*new_usr, content);
			}
		}
	}
	else
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 401) + ERR_NOSUCHNICK((args[1])));
}

void	channel_privmsg(Chan &chan, Users &sender, std::string content)
{
	std::string to_send = ":" + sender.getFull_id() + " PRIVMSG " + chan.getName() + " " + content;
	v_Users_ptr vect = chan.getUsers();
	for (v_Users_ptr::iterator it = vect.begin(), ite = vect.end(); it != ite; it++)
	{
		if (**it != sender)
		{
			send_packets(**it, to_send);
		}
	}
}
