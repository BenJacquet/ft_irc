/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_display.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:41:22 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 17:46:33 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief displays an error
 * 
 * @param error string containing the error
 */
void put_error(std::string const error)
{
	CERR(RED, "Error: " + error);
}

/**
 * @brief displays usage of ircserv
 * 
 */
void put_usage()
{
	put_error("ircserv: bad number of arguments.");
	COUT(CYAN, "Usage: ircserc: ./ircserv <port> <password>") << std::endl;
	COUT(CYAN, "port :");
	COUT(CYAN, "the port number on which your IRC server will be listening to for incoming IRC connections.") << std::endl;
	COUT(CYAN, "password :");
	COUT(CYAN, "the connection password. It will be needed by any IRC client that tries to connect to your server.");
}

void server_shutdown()
{
	g_log << "SERVER SHUTDOWN AFTER " << time(NULL) - g_start << "seconds";
	exit(1);
}