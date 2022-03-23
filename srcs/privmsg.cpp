/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:50:41 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/23 15:18:59 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	command_privmsg(t_data &data, Message &cmd)
{
	Chan	*new_chan;
	v_Users::iterator	new_usr;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	std::string content;
	for(size_t i=2; i < args.size(); i++)
		content += args[i] + " " ;
	if (((new_chan = is_chan_exist(data, args[1])) != NULL) ||
		(new_usr = find_client_nick(data, args[1])) != data.users.end())
	{
		if (new_chan != NULL)
			channel_privmsg(*new_chan, *cmd.getSender(), content);
		else
		{
			content = ":" + cmd.getSender()->getFull_id() + " PRIVMSG " +\
				find_client_nick(data, args[1])->getNick_name() + " " + content;
			send_packets(new_usr->getFd(), content);
		}
	}
	else
		CERR(RED, "User or Channel " << args[1] << "not found\n");
}

void	channel_privmsg(Chan &chan, Users &sender, std::string content)
{
	std::string to_send = ":" + sender.getFull_id() + " PRIVMSG " + chan.getTopic() + " " + content;
	v_Users vect = chan.getUsers();
	for (v_Users::iterator it = vect.begin(), ite = vect.end(); it != ite; it++)
	{
		if (it->getFd() != sender.getFd())
		{
			send_packets(it->getFd(), to_send);
		}
	}
}