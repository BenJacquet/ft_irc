/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_display.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:41:22 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/02 12:41:38 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void put_error(std::string const error)
{
	CERR(RED, "Error: " + error);
}

void put_usage()
{
	put_error("ircserv: bad number of arguments.");
	COUT(CYAN, "Usage: ircserc: ./ircserv <port> <password>") << std::endl;
	COUT(CYAN, "port :");
	COUT(CYAN, "the port number on which your IRC server will be listening to for incoming IRC connections.") << std::endl;
	COUT(CYAN, "password :");
	COUT(CYAN, "the connection password. It will be needed by any IRC client that tries to connect to your server.");
}

void put_connection(int client_fd)
{
	COUT(GREEN, "Successfully connected with " << client_fd);
}

void put_disconnection(int client_fd)
{
	COUT(YELLOW, "Lost connection with " << client_fd);
}