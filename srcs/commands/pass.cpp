/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:04:24 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/20 16:21:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

/**
 * @brief Parses the PASS command received
 * 
 * @param data 
 * @param cmd 
 */
void	command_pass(t_data &data, Message &cmd)
{
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	sender->setReg_status(3);
	if (sender->getPw().empty() == false)
		send_packets(*sender, create_reply(data, sender, 462, ""));
	else if (args.size() == 1 || args[1].empty() == true)
		send_packets(*sender, create_reply(data, sender, 461, args[0]));
	else
		sender->setPw(encrypt_data(data.salt, args[1]));
}