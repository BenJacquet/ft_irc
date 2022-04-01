/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:04:24 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 17:06:11 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	command_pass(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	sender->setReg_status(3);
	if (sender->getPw().empty() == false)
		send_packets(*sender, create_reply(data, sender, 462, ""));
	if (args.size() == 1 || args[1].empty() == true)
		send_packets(*sender, create_reply(data, sender, 461, args[0]));
	sender->setPw(encrypt_data(data.salt, args[1]));
	// check user password and authenticate if valid
}