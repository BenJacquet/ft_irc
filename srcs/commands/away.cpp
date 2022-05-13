/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 06:44:58 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/13 20:47:59 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	away_parsing(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args.size() == 1)
	{
		send_packets(*cmd.getSender(), create_reply(data, cmd.getSender(), 461, args[0]));
		return ;
	}
	Users *client = cmd.getSender();

	if (client->getNick_name() != args[1].erase(0, 1))
	{
		send_packets(*cmd.getSender(), create_reply(data, cmd.getSender(), 502, ""));
		return ;
	}
	if (client->getMode().find("a") != std::string::npos)
	{
		client->setMode(client->getMode().erase(client->getMode().find("a"), 1));
		send_packets(*client, create_reply(data, client, 305, ""));
		send_packets(*client, RPL_MODE(client->getNick_name(), "-a"));
	}
	else
	{
		client->setMode(client->getMode() + "a");
		std::string Away_mode("");
		for (std::vector<std::string>::iterator it = args.begin() + 2, ite = args.end(); \
		it != ite; it++)
		{
			if (it == args.begin() + 2)
				Away_mode = *it;
			else 
				Away_mode += " " + *it;
		}
		client->setAway_mode(Away_mode);
		send_packets(*client, create_reply(data, client, 306, ""));
		send_packets(*client, RPL_MODE(client->getNick_name(), "+a"));
	}
}
