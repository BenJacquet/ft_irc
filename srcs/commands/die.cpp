/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:05:11 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 17:11:06 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	command_die(t_data &data, Message &cmd) // AJOUTER CHECK DES MODES
{
	(void)data;
	(void)cmd;
	Users *sender = cmd.getSender();

	if (sender->getMode().find_first_of("o", 0) != std::string::npos)
		server_shutdown();
	else
		send_packets(*sender, create_reply(data, sender, 481, ""));
	// checks for privileges and kills server
}