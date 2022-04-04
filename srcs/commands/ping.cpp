/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:04:56 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/04 11:35:23 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

/**
 * @brief Parses the PING command received and answers with a PONG containing the same arguments
 * 
 * @param data 
 * @param cmd 
 */
void	command_ping(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();

	std::string pong = cmd.getPayload().replace(0, 4, "PONG");
	send_packets(*sender, pong);
	// replies to ping messages from clients
}