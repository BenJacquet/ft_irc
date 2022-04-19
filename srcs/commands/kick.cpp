/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:07:42 by thoberth          #+#    #+#             */
/*   Updated: 2022/04/19 16:02:52 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	kick_parsing(t_data &data, Message &cmd)
{
	Users &sender = *cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args.size() < 4)
	{
		send_packets(sender, create_reply(data, &sender, 461, args[0]));
		return ;
	}
	std::string content = args[3];
	for (size_t i = 4; i < args.size() ; i++)
		content += " " + args[i];
	Chan *new_chan = is_chan_exist(data, args[1]);
	if (new_chan == NULL)
	{
		send_packets(sender, create_reply(data, &sender, 403, args[1]));
		return ;
	}
	if (sender.getMode().find("oO") == std::string::npos && sender != new_chan->getCreator())
	{
		send_packets(sender, create_reply(data, &sender, 482, new_chan->getName()));
		return ;
	}
	Users &target = *find_client_nick(data, args[2]);
	v_Users vect = new_chan->getUsers();
	v_Users::iterator it = vect.begin();
	for (v_Users::iterator ite = vect.end(); it != ite && *it != target; it++)
		;
	if (it == vect.end())
	{
		send_packets(sender, create_reply(data, &sender, 441, args[2] + " " + new_chan->getName()));
		return ;
	}
	if (new_chan->rmusers(target))
	{
		it = vect.begin();
		for (v_Users::iterator ite = vect.end(); it != ite; it++)
			send_packets(*it, ":" + sender.getFull_id() + " KICK " + args[1] + " "\
			+ args[2] + content);
	}
}
