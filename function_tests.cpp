/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_tests.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:22:12 by jabenjam          #+#    #+#             */
/*   Updated: 2022/02/23 17:53:46 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function_tests.hpp"

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
	int		sockfd;
	struct	sockaddr_in my_addr;
	int		port;

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "Error: cannot create socket fd" << std::endl; // Remplacer par une exception ou meilleur message sur std::cerr
		return (-1);
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons();
	return (0);
}