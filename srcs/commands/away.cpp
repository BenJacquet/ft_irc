/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 06:44:58 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/21 11:05:55 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	away_parsing(t_data &data, Message &cmd)
{
	(void)data;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	Users *client = cmd.getSender();
	if (args.size() == 1 && client->getMode().find("a") != std::string::npos)
	{
		client->setMode(client->getMode().erase(client->getMode().find("a"), 1));
		send_packets(*client, create_reply(client, 305) + RPL_UNAWAY());
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
	send_packets(*client, create_reply(client, 306) + RPL_NOAWAY());
	if (client->getMode().find("a") == std::string::npos)
	{
		client->setMode(client->getMode() + "a");
		send_packets(*client, RPL_MODE(client->getNick_name(), "+a"));
	}
}
