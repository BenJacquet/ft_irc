/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:04:41 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/21 10:54:31 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

/**
 * @brief Gives the operator privileges to the user if the password is correct
 * 
 * @param data 
 * @param cmd 
 */
void	command_oper(t_data &data, Message &cmd) // ajouter un message MODE renvoyé a l'utilisateur
{
	Users		*sender = cmd.getSender();
	std::string	mode = sender->getMode();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	if (args.size() < 3 || args[1].empty() == true || args[2].empty() == true)
		send_packets(*sender, create_reply(sender, 461) + ERR_NEEDMOREPARAMS(args[0]));
	else if (sender->getNick_name().compare(args[1]) != 0)
		send_packets(*sender, create_reply(sender, 502) + ERR_UMODEUNKNOWNFLAG());
	else if (data.password.compare(encrypt_data(data.salt, args[2])) != 0)
		send_packets(*sender, create_reply(sender, 464) + ERR_PASSWDMISMATCH());
	else
	{
		if (sender->getMode().find_first_of("o", 0) == std::string::npos)
		{
			sender->setMode(mode + "o");
			send_packets(*sender, RPL_MODE(sender->getNick_name(), sender->getMode()));
		}
		send_packets(*sender, create_reply(sender, 381) + RPL_YOUREOPER());
	}
}