/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_operations.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:24:58 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/30 07:49:08 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

std::ofstream	g_log("log.txt");

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

void	log_coms(Users &client, std::string &to_log, bool out)
{
	time_t my_time = time(NULL);

	if (out == true)
		g_log << "TO ---> ";
	else
		g_log << "FROM <--- ";
	g_log
		<< (client.getFull_id().empty() == true ? "Unregistered" : client.getFull_id())
		<< " "
		<< client.getIp()
		<< " - "
		<< ctime(&my_time)
		<< std::endl
		<< to_log
		<< std::endl;
}

/**
 * @brief fonction qui pour utiliser send(), de maniere safe
 * renvoie la taille envoye ou -1 si send() echoue
 * 
 * @param client client to send packets
 * @param to_send the param to send to client
 */
int send_packets(Users &client, std::string to_send)
{
	int len = to_send.length();
	int ret = 0;
	to_send += "\r\n";
	while (ret < len && ret != -1)
		ret += send(client.getFd(), to_send.c_str(), to_send.size(), MSG_NOSIGNAL);
	if (ret == -1)
		CERR(YELLOW, "couldn't send packet!");
	else
	{
		COUT(L_BLUE, "----> sent " << ret << " bytes to " << client.getFd() << ":");
		log_coms(client, to_send.replace(len, 1, "\0"), true);
		COUT(L_BLUE, to_send);
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
		std::string log_buffer(buffer);
		log_coms(client, log_buffer, false);
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