/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:04:56 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 17:15:07 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	command_ping(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();

	std::string pong = cmd.getPayload().replace(0, 4, "PONG");
	send_packets(*sender, pong);
	// replies to ping messages from clients
}