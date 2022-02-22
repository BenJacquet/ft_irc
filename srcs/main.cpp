/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:20:43 by jabenjam          #+#    #+#             */
/*   Updated: 2022/02/22 16:20:51 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

int		irc_loop()
{
	std::string cmd;
	while (1)
	{
		cmd.clear();
		std::getline(std::cin, cmd);
		if (cmd.compare("/quit") == 0 || std::cin.eof()) // ajouter arguments du /quit [message]
			break;
	}
	return (0);
}

int		main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Error: ircserv: Bad number of arguments." << std::endl;
		std::cout << "Usage: ircserc: ./ircserv <port> <password>" << std::endl << std::endl;
		std::cout << "port :" << std::endl << "the port number on which your IRC server will be listening to for incoming IRC connections." << std::endl << std::endl;
		std::cout << "password :" << std::endl << "the connection password. It will be needed by any IRC client that tries to connect to your server." << std::endl;
		return (1);
	}
	static_cast<void>(ac);
	static_cast<void>(av);
	std::cout << ASCII_HEADER << std::endl;
	// parse_arguments();
	return (irc_loop(/*args*/));
}