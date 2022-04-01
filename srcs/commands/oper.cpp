/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:04:41 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 17:06:43 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	command_oper(t_data &data, Message &cmd) // ajouter un message MODE renvoyé a l'utilisateur
{
	Users		*sender = cmd.getSender();
	std::string	mode = sender->getMode();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	if (args.size() < 3 || args[1].empty() == true || args[2].empty() == true)
		send_packets(*sender, create_reply(data, sender, 461, args[0]));
	else if (data.password.compare(encrypt_data(data.salt, args[2])) != 0)
		send_packets(*sender, create_reply(data, sender, 464, ""));
	else
	{
		if (sender->getMode().find_first_of("o", 0) == std::string::npos)
			sender->setMode(mode + "o"); // ajouter un message MODE renvoyé a l'utilisateur
		send_packets(*sender, create_reply(data, sender, 381, ""));
	}
}