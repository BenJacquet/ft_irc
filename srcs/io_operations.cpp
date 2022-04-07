/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_operations.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:24:58 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/07 15:27:02 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief Creates a reply containing the full_id of the client
 * and the numeric reply corresponding to the code received as argument
 * 
 * @param data 
 * @param client 
 * @param code the code of the numeric reply
 * @param arg argument sent to client if needed
 * @return std::string 
 */
std::string create_reply(t_data &data, Users *client, int code, std::string arg)
{
	std::string reply;
	std::stringstream code_str;
	code_str << code;
	(void)data; // a degager

	if (client->getNick_name().empty() == true)
		reply = ":" + client->getHost_name() + " " + (code == 1 ? "00" : "") + code_str.str() + " * ";
	else
		reply = ":" + client->getHost_name() + " " + (code == 1 ? "00" : "") + code_str.str() + " " + client->getNick_name() + " ";
	switch (code)
	{
		case (001):
			return (reply + RPL_WELCOME(client->getFull_id()));
		case (221):
			return (reply + RPL_UMODEIS(client->getMode()));
		case (324):
			return (reply + RPL_CHANNELMODEIS(arg));
		case (381):
			return (reply + RPL_YOUREOPER());
		case (431):
			return (reply + ERR_NONICKNAMEGIVEM());
		case (432):
			return (reply + ERR_ERRONEUSNICKNAME(arg));
		case (433):
			return (reply + ERR_NICKNAMEINUSE(arg));
		case (461):
			return (reply + ERR_NEEDMOREPARAMS(arg));
		case (462):
			return (reply + ERR_ALREADYREGISTERED());
		case (464):
			return (reply + ERR_PASSWDMISMATCH());
		case (471):
			return (reply + ERR_CHANNELISFULL(arg));
		case (475):
			return (reply + ERR_BADCHANNELKEY(arg));
		case (481):
			return (reply + ERR_NOPRIVILEGE());
		case (501):
			return (reply + ERR_UMODEUNKNOWNFLAG());
		case (502):
			return (reply + ERR_USERMISMATCH());
		case (900):
			return (reply + RPL_MODE(client->getNick_name(), arg));
		default:
			break;
	}
	return ("");
}

/**
 * @brief Logs all communications inside a file whose name is specified in the ft_irc.hpp
 * 
 * @param client 
 * @param to_log data to log
 * @param out true = data sent | false = data received
 */
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
		<< "\t"
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
	char buffer[BUFFERSIZE];
	std::string buffer_str;
	ssize_t received = 0;
	ssize_t sum = 0;

	buffer_str.clear();

	while (1)
	{
		received = recv(client.getFd(), buffer, BUFFERSIZE, 0);
		if (received <= 0)
			break;
		sum += received;
		buffer_str += buffer;
		std::memset(buffer, 0, BUFFERSIZE);
	}
	if (sum == 0)
		disconnect_user(data, client);
	else if (sum != -1)
	{
		remove_carriage(buffer_str);
		std::string log_buffer(buffer_str.c_str());
		log_coms(client, log_buffer, false);
		COUT(L_GREEN, "<---- received " << sum << " bytes from " << client.getFd() << ":");
		COUT(L_GREEN, buffer_str.c_str());
		command_parsing(data, client, buffer_str.c_str());
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