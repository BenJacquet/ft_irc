/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 06:44:58 by thoberth          #+#    #+#             */
/*   Updated: 2022/04/11 16:21:24 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	away_parsing(t_data &data, Message &cmd)
{
	Users *client = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	if (client->getMode().find("a") != std::string::npos)
	{
		client->setMode(client->getMode().erase(client->getMode().find("a"), 1));
		send_packets(*client, create_reply(data, client, 305, ""));
		send_packets(*client, create_reply(data, client, 900, client->getMode()));
	}
	else
	{
		client->setMode(client->getMode() + "a");
		client->setAway_mode(args[1].erase(0, 1));
		for (std::vector<std::string>::iterator it = args.begin() + 2, ite = args.end(); \
		it != ite; it++)
			client->setAway_mode(client->getAway_mode() + " "  + *it);
		send_packets(*client, create_reply(data, client, 306, ""));
		send_packets(*client, create_reply(data, client, 900, client->getMode()));
	}
}
