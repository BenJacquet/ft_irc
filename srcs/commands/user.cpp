/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:04:13 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/20 18:00:17 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

/**
 * @brief Parses the USER command received
 * 
 * @param data 
 * @param cmd 
 */
void	command_user(t_data &data, Message &cmd)
{
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	if (args.size() < 5)
		send_packets(*sender, create_reply(data, sender, 461, args[0]));
	else if (sender->getUser_name().empty() == false)
		send_packets(*sender, create_reply(data, sender, 462, ""));
	else
	{
		sender->setReg_status((sender->getUser_name().empty() == true ? 2 : sender->getReg_status()));
		sender->setReg_status((sender->getPw().empty() == true ? sender->getReg_status() : 3));
		sender->setUser_name(args[2]);
		sender->setHostname(args[3]);
		sender->setReal_name((&args[4][1] + (args.size() == 6 ? " " + args[5] : "")));
		sender->setFull_id(sender->getNick_name() + "!" + args[2] + "@" + args[3]);
		if (sender->getOnline() == false && sender->getIn_use() == false)
			registration(data, sender);
	}
}