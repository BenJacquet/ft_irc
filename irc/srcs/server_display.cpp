/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_display.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:41:22 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/04 11:57:44 by jabenjam         ###   ########.fr       */
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

/**
 * @brief Displays a p
 * 
 */
void server_shutdown()
{
	time_t end = (time(NULL) - g_start);
	g_log << "Server shutdown after " << end << " seconds of activity";
	COUT(WHITE, "Server shutdown after " << end << " seconds of activity");
	exit(1);
}