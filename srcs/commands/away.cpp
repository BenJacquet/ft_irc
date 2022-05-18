/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 06:44:58 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/18 14:22:00 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	away_parsing(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(cmd.getPayload());
	Users *client = cmd.getSender();
	if (args.size() == 1 && client->getMode().find("a") != std::string::npos)
	{
		client->setMode(client->getMode().erase(client->getMode().find("a"), 1));
		send_packets(*client, create_reply(data, client, 305, ""));
		send_packets(*client, RPL_MODE(client->getNick_name(), "-a"));
		return ;
	}
	std::string Away_mode("");
	for (std::vector<std::string>::iterator it = args.begin() + 1, ite = args.end(); \
	it != ite; it++)
	{
		if (it == args.begin() + 1)
			Away_mode = it->erase(0,1);
		else 
			Away_mode += " " + *it;
	}
	client->setAway_mode(Away_mode);
	send_packets(*client, create_reply(data, client, 306, ""));
	if (client->getMode().find("a") == std::string::npos)
	{
		client->setMode(client->getMode() + "a");
		send_packets(*client, RPL_MODE(client->getNick_name(), "+a"));
	}
}
