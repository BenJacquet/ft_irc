/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_operations.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:24:58 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/28 14:16:07 by jabenjam         ###   ########.fr       */
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
	int len = to_send.size();
	int ret = 0;
	to_send += "\r\n";
	while (ret < len && ret != -1)
		ret += send(client, to_send.c_str(), to_send.size(), MSG_NOSIGNAL);
	if (ret == -1)
		CERR(YELLOW, "couldn't send packet!");
	else
	{
		COUT(L_BLUE, "----> sent " << ret << " bytes to " << client << ":");
		COUT(L_BLUE, to_send);
	}
	return (ret);
}

std::string create_reply(t_data &data, Users *client, int code, std::string arg)
{
	std::string reply;
	std::stringstream code_str;
	code_str << code;
	(void)data;
	(void)arg;

	if (client->getNick_name().empty() == true)
		reply = ":" + client->getHost_name() + " " + (code == 1 ? "00" : "") + code_str.str() + " * ";
	else
		reply = ":" + client->getHost_name() + " " + (code == 1 ? "00" : "") + code_str.str() + " " + client->getNick_name() + " ";
	switch (code)
	{
		case (001):
			return (reply + RPL_WELCOME(client->getFull_id()));
		case (433):
			return (reply + ERR_NICKNAMEINUSE(arg));
		default:
			break;
	}
	return ("");
}

/**
 * @brief receives packets from fd
 * 
 * @param data 
 * @param client fd to receive from
 * @return amount of bytes received
 */
int receive_packets(t_data &data, Users &client)
{
	char buffer[BUFFERSIZE]; // peut etre passer sur std::string et append
	//std::istringstream buffer;
	int received = 0;

	std::memset(buffer, 0, BUFFERSIZE);
	received = recv(client.getFd(), buffer, BUFFERSIZE, 0);
	if (received == 0)
		disconnect_user(data, client);
	else if (received != -1)
	{
		COUT(L_GREEN, "<---- received " << received << " bytes from " << client.getFd() << ":");
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
void io_loop(t_data &data, Users &client)
{
	receive_packets(data, client);
}