/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_operations.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:24:58 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/11 17:33:35 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief fonction qui pour utiliser send(), de maniere safe
 * renvoie la taille envoye ou -1 si send() echoue
 * 
 * @param client client to send packets
 * @param to_send the param to send to client
 */
int send_packets(int client, std::string to_send)
{
	int len = to_send.length();
	int ret = 0;
	while (ret < len && ret != -1)
		ret += send(client, to_send.c_str() + ret, len - ret, MSG_NOSIGNAL);
	if (ret == -1)
		CERR(YELLOW, "couldn't send packet!");
	else
	{
		COUT(CYAN, "----> sent " << ret << " bytes to " << client << ":");
		COUT(CYAN, to_send);
	}
	return (ret);
}

/**
 * @brief receives packets from fd
 * 
 * @param data 
 * @param client fd to receive from
 * @return amount of bytes received
 */
int receive_packets(t_data &data, Users* client)
{
	char buffer[BUFFERSIZE]; // peut etre passer sur un vecteur contenant les paquets entiers
	//std::istringstream buffer;
	int received = 0;

	std::memset(buffer, 0, BUFFERSIZE);
	received = recv(client->getFd(), buffer, BUFFERSIZE, 0);
	if (received == 0)
	{
		COUT(CYAN, received);
		put_disconnection(client->getFd());
		remove_fd(data, client->getFd());
	}
	else if (received != -1)
	{
		COUT(L_GREEN, "<---- received " << received << " bytes from " << client << ":");
		COUT(L_GREEN, buffer);
		command_parsing(data, client, buffer);
	}
	return (received);
}

/**
 * @brief main i/o operations loop
 * 
 * @param data 
 * @param it iterator pointing to fd
 */
void io_loop(t_data &data, Users& client)
{
	int i = 0;
	COUT(WHITE, "IOLOOP CLIENT FD=" << client.getFd());
	while (1)
	{
		if ((i = receive_packets(data, &client) < 1))
			return;
		// if (send_packets(it->fd) == -1)
	}
}