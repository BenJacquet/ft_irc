/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_tests.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:22:12 by jabenjam          #+#    #+#             */
/*   Updated: 2022/02/24 17:30:22 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function_tests.hpp"

#define BACKLOG 10

void	put_error(std::string const error)
{
	CERR(RED, "Error: " + error);
}

void	put_usage()
{
	put_error("ircserv: bad number of arguments.");
	COUT(CYAN, "Usage: ircserc: ./ircserv <port> <password>") << std::endl;
	COUT(CYAN, "port :");
	COUT(CYAN, "the port number on which your IRC server will be listening to for incoming IRC connections.") << std::endl;
	COUT(CYAN, "password :");
	COUT(CYAN, "the connection password. It will be needed by any IRC client that tries to connect to your server.");
}

void	put_connection(char const *client_ip)
{
	COUT(GREEN, "Successfully connected with " << client_ip);
}

void	put_disconnection(char const *client_ip)
{
	COUT(YELLOW, "Lost connection with " << client_ip);
}

bool	valid_port(std::string av, t_data & data)
{
	if (av.length() > 0)
	{
		if (av.find_first_not_of("0123456789") != std::string::npos)
			return (false);
		int	port = atoi(av.c_str());
		if (port < 1025 || port > 65535)
			return (false);
		data.port = static_cast<uint16_t>(port);
		return (true);
	}
	return (false);
}

// int		receive_packets(t_data & data, client_map::iterator client)
// {
// 	char	buff[BUFFERSIZE]; // peut etre passer sur un vecteur contenant les paquets entiers
// 	int		received = 0;

// 	received = recv(client->first(), buff, BUFFERSIZE, 0);
// }

int		command_loop(t_data & data)
{
	std::string		cmd;

	cmd.clear();
	std::getline(std::cin, cmd);
	if (cmd.compare("/quit") == 0 || std::cin.eof())
		return (1);
	return (0);
}

int		irc_loop(t_data & data)
{
	int						tmp_fd;
	struct sockaddr_in		tmp_client_sock;
	socklen_t				size = sizeof(struct sockaddr_in);
	client_map::iterator	it = data.client_socks.begin();
	client_map::iterator	end = data.client_socks.end();

	// fcntl(0, F_SETFL, O_NONBLOCK);
	while (1)
	{
		if ((tmp_fd = accept(data.sock_fd,
			reinterpret_cast<struct sockaddr*>(&tmp_client_sock), &size) == -1))
		{
			put_error("cannot accept new connection");
			return (1);
		}
		put_connection(inet_ntoa(tmp_client_sock.sin_addr));
		data.client_socks.insert(client_pair(tmp_fd, tmp_client_sock));
		// if (command_loop(data) == 1)
		// 	return (0);
		while (1)
		{
			for (it = data.client_socks.begin(); it != end; it++)
				receive_packets(data, it);
		}
	}
	return (0);
}

int		server_setup(t_data & data)
{
	// TESTS SOCKET
	int		listenfd;
	int		port;

	if ((data.sock_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		put_error("cannot create socket fd");
		return (1);
	}

	data.server_sock.sin_family = AF_INET;
	data.server_sock.sin_port = htons(data.port);
	data.server_sock.sin_addr.s_addr = INADDR_ANY;

	if (bind(data.sock_fd, reinterpret_cast<struct sockaddr*>(&data.server_sock), sizeof(struct sockaddr)) == -1)
	{
		put_error("cannot bind, port is already in use.");
		// perror(strerror(errno)); // remplacer par une fonction autorisee
		return (1);
	}

	if ((listenfd = listen(data.sock_fd, BACKLOG)) == -1)
	{
		put_error("cannot listen, port is already in use.");
		// perror(strerror(errno)); // remplacer par une fonction autorisee
		return (1);
	}
	return (0);
}

int		test_getaddrinfo(t_data & data, char **av)
{
	// TESTS GETADDR_INFO
	std::memset(&(data.server_sock.sin_zero), '\0', 8);
	struct	addrinfo hints, *info, *info_ptr;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo("127.0.0.1", av[1], &hints, &info) != 0)
	{
		perror(strerror(errno)); // remplacer par une fonction autorisee
		return (1);
	}
	// info_ptr->ai_family = AF_INET si IPv4 || AF_INET6 si IPv6
	// cast en (sockaddr_in ou sockaddr_in6 selon protocole)
	freeaddrinfo(info);
	return (0);
}

int		parse_arguments(int ac, char **av, t_data & data)
{
	// ARGUMENTS ERROR MANAGEMENT
	if (ac != 3)
	{
		put_usage();
		return (1);
	}
	if (valid_port(static_cast<std::string>(av[1]), data) == false)
	{
		put_error("ircserv: invalid port, valid port range is 1025-65535.");
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_data	data;

	if (parse_arguments(ac, av, data) != 0 || server_setup(data) != 0)
		return (1);
	irc_loop(data);
	return (0);
}