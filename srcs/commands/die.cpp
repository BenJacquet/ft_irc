/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:05:11 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/03 17:13:47 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

/**
 * @brief Kills the server if the sender has operator privileges
 * 
 * @param data 
 * @param cmd 
 */
void	command_die(t_data &data, Message &cmd)
{
	Users *sender = cmd.getSender();

	if (sender->getMode().find_first_of("o", 0) != std::string::npos)
		server_shutdown();
	else
		send_packets(*sender, create_reply(data, sender, 481, ""));
}
