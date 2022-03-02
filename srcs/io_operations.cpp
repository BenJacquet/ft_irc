/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_operations.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:24:58 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/02 13:19:49 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/*
**	fonction qui pour utiliser send(), de maniere safe
**	renvoie la taille envoye ou -1 si send() echoue
*/
int send_packets(int client, char *to_send)
{
	int len = ft_strlen(to_send);
	int ret = 0;
	while (ret < len && ret != -1)
		ret += send(client, to_send + ret, len - ret, 0);
	if (ret == -1)
		CERR(YELLOW, "couldn't send packet!");
	else
	{
		COUT(L_GREEN, "----> sent " << ret << " bytes to " << client << ":");
		COUT(L_GREEN, to_send);
	}
	return (ret);
}

int receive_packets(t_data &data, int client)
{
	char buff[BUFFERSIZE]; // peut etre passer sur un vecteur contenant les paquets entiers
	int received = 0;

	std::memset(buff, 0, BUFFERSIZE);
	static_cast<void>(data);
	received = recv(client, buff, BUFFERSIZE, 0);
	if (received == 0)
	{
		COUT(CYAN, received);
		put_disconnection(client);
		remove_fd(data, client);
	}
	else if (received != -1)
	{
		COUT(L_GREEN, "<---- received " << received << " bytes from " << client << ":");
		COUT(L_GREEN, buff);
		send_packets(client, buff);
	}
	return (received);
}

/**
 * @brief 
 * 
 * @param data 
 * @param it 
 */
void io_loop(t_data &data, pollfds::iterator it)
{
	int i = 0;
	while (1)
	{
		if ((i = receive_packets(data, it->fd) < 1))
			return;
		// if (send_packets(it->fd) == -1)
	}
}