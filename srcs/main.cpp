/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:20:43 by jabenjam          #+#    #+#             */
/*   Updated: 2022/02/28 17:51:26 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

#define BACKLOG 10

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

bool valid_port(std::string av, t_data &data)
{
	if (av.length() > 0)
	{
		if (av.find_first_not_of("0123456789") != std::string::npos)
			return (false);
		int port = atoi(av.c_str());
		if (port < 1024 || port > 65535)
			return (false);
		data.port = static_cast<uint16_t>(port);
		return (true);
	}
	return (false);
}

pollfds::iterator	find_fd(t_data &data, int fd)
{
	pollfds::iterator it = data.poll_fds.begin();
	pollfds::iterator end = data.poll_fds.end();

	for (; it != end; it++)
	{
		if (it->fd == fd)
			return (it);
	}
	return (end);
}

void	remove_fd(t_data &data, int fd)
{
	pollfds::iterator end = data.poll_fds.end();
	pollfds::iterator found = find_fd(data, fd);

	if (found == end)
		return;
	data.poll_fds.erase(found);
}

void	add_fd(t_data &data, int fd)
{
	pollfds::iterator	end = data.poll_fds.end();
	pollfds::iterator	found = find_fd(data, fd);
	struct pollfd		poll;

	poll.fd = fd;
	poll.events = (POLLIN | POLLOUT | POLLHUP | POLLNVAL);
	poll.revents = 0;
	if (found != end)
		return;
	data.poll_fds.push_back(poll);
}

int receive_packets(t_data &data, int client)
{
	char buff[BUFFERSIZE]; // peut etre passer sur un vecteur contenant les paquets entiers
	int received = 0;

	std::memset(buff, 0, BUFFERSIZE);
	static_cast<void>(data);
	received = recv(client, buff, BUFFERSIZE, 0);
	if (received < 1)
	{
		put_disconnection(client);
		remove_fd(data, client);
	}
	else
	{
		COUT(WHITE, "received " << received << " bytes:");
		COUT(WHITE, buff);
	}
	return (0);
}

int command_loop(t_data &data)
{
	std::string cmd;
	static_cast<void>(data);

	cmd.clear();
	if (std::cin.peek() != EOF)
	{
		std::getline(std::cin, cmd);
		if (cmd.compare("/quit") == 0 || std::cin.eof())
			return (1);
	}
	return (0);
}

int	new_connection(t_data &data)
{
	int client_fd;
	struct sockaddr_in client_sock;
	socklen_t size = sizeof(struct sockaddr_storage);

	if ((client_fd = accept(data.sock_fd,
					 reinterpret_cast<struct sockaddr *>(&client_sock), &size) == -1))
		return (-1);
	put_connection(client_fd);
	add_fd(data, client_fd);
	return (client_fd);
}

int	poll_setup(t_data &data)
{
	int	poll_r = poll(data.poll_fds, data.poll_fds.size(), data.timeout);
	pollfds::iterator	it = data.poll_fds.begin();
	pollfds::iterator	end = data.poll_fds.end();

	if (poll_r < 0)
	{
		CERR(YELLOW, "poll()");
		return (1);
	}
	else if (poll_r == 0)
	{
		CERR(YELLOW, "poll() timeout.")
		return (1);
	}
	for (; it != end; it++)
	{
		if (it->revents == 0)
			continue;
		else if (it->revents != POLLIN)
			CERR(YELLOW, "revent= " << it->revents);
		if (it->fd == data.sock_fd)
		{
			while (1)
			{
				if (new_connection(data) == -1)
					break;
			}
		}
		else
		{
			COUT(WHITE, );
		}
	}
	return (0);
}

int irc_loop(t_data &data)
{
	while (1)
	{
		// if (command_loop(data) == 1)
		// 	return (0);
		if (poll_setup() == 1)
			return (1);
		receive_packets(data, client_fd);
	}
	return (0);
}

int addrinfo_setup(t_data &data, char **av)
{
	// TESTS GETADDR_INFO
	struct addrinfo hints;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(0, av[1], &hints, &data.bind_addr) != 0)
	{
		put_error("getaddrinfo()");
		return (1);
	}
	// info_ptr->ai_family = AF_INET si IPv4 || AF_INET6 si IPv6
	// cast en (sockaddr_in ou sockaddr_in6 selon protocole)
	return (0);
}

int server_setup(t_data &data)
{
	data.timeout = (3 * 60 * 1000);
	add_fd(data, data.sock_fd);
	// TESTS SOCKET
	if ((data.sock_fd = socket(data.bind_addr->ai_family,
							   data.bind_addr->ai_socktype, data.bind_addr->ai_protocol)) == -1)
	{
		put_error("socket()");
		return (1);
	}

	if (bind(data.sock_fd, data.bind_addr->ai_addr, data.bind_addr->ai_addrlen) == -1)
	{
		put_error("bind()");
		// perror(strerror(errno)); // remplacer par une fonction autorisee
		return (1);
	}

	if (listen(data.sock_fd, BACKLOG) == -1)
	{
		put_error("listen()");
		// perror(strerror(errno)); // remplacer par une fonction autorisee
		return (1);
	}
	return (0);
}

int parse_arguments(int ac, char **av, t_data &data)
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

int main(int ac, char **av)
{
	t_data data;

	if (parse_arguments(ac, av, data) != 0 || addrinfo_setup(data, av) != 0 || server_setup(data) != 0)
		return (1);
	COUT(L_CYAN, ASCII_HEADER);
	irc_loop(data);
	freeaddrinfo(data.bind_addr);
	return (0);
}