/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:20:43 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/01 17:45:00 by jabenjam         ###   ########.fr       */
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

pollfds::iterator find_fd(t_data &data, int fd)
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

void remove_fd(t_data &data, int fd)
{
	pollfds::iterator end = data.poll_fds.end();
	pollfds::iterator found = find_fd(data, fd);

	if (found == end)
		return;
	FD_FREE(data.poll.fds);
	close(fd); // check si interdit ou non
	data.poll_fds.erase(found);
}

void add_fd(t_data &data, int fd)
{
	pollfds::iterator end = data.poll_fds.end();
	pollfds::iterator found = find_fd(data, fd);
	struct pollfd poll;
	// int	reuse = 1;

	// if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
	// {
	// 	perror("setsockopt");
	// 	exit(1);
	// }
	poll.fd = fd;
	poll.events = (POLLIN /* | POLLOUT | POLLHUP | POLLNVAL*/);
	poll.revents = 0;
	if (found != end)
		return;
	fcntl(fd, F_SETFL, O_NONBLOCK);
	data.poll_fds.push_back(poll);
	COUT(CYAN, "added descriptor to pollfd vector" << poll.fd);
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

int new_connection(t_data &data)
{
	struct sockaddr_in client_sock;
	socklen_t size = sizeof(struct sockaddr_storage);
	int client_fd = accept(data.sock_fd, reinterpret_cast<struct sockaddr *>(&client_sock), &size);

	if (client_fd < 1)
	{
		CERR(YELLOW, "accept()");
		return (-1);
	}
	put_connection(client_fd);
	add_fd(data, client_fd);
	return (client_fd);
}

int ft_strlen(char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return (i);
}

/*
**	fonction qui pour utiliser send(), de maniere safe
**	renvoie la taille envoye ou -1 si send() echoue
*/
int send_packets(int client_fd, char *to_send)
{
	int len = ft_strlen(to_send);
	int ret = 0;
	while (ret < len && ret != -1)
		ret += send(client_fd, to_send + ret, len - ret, 0);
	if (ret == -1)
		CERR(YELLOW, "couldn't send packet!");
	else
	{
		COUT(L_GREEN, "----> sent " << ret << " bytes:");
		COUT(L_GREEN, to_send);
	}
	return (ret);
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
		COUT(L_GREEN, "<---- received " << received << " bytes:");
		COUT(L_GREEN, buff);
		send_packets(client, buff);
	}
	return (received);
}

void io_loop(t_data &data, pollfds::iterator it)
{
	int i = 0;
	while (1)
	{
		if ((i = receive_packets(data, it->fd) < 1))
			return;
		// if (send_packets(it->fd) == -1)
	}
}

int poll_setup(t_data &data)
{
	int poll_r = poll(reinterpret_cast<struct pollfd *>(&data.poll_fds[0]), data.poll_fds.size(), data.timeout);
	pollfds::iterator it = data.poll_fds.begin();
	pollfds::iterator end = data.poll_fds.end();

	if (poll_r < 0)
	{
		CERR(YELLOW, "poll()");
		return (1);
	}
	else if (poll_r == 0)
	{
		CERR(YELLOW, "poll() timeout.");
		return (1);
	}
	for (it = data.poll_fds.begin(); it != end; it++)
	{
		COUT(WHITE, "(" << &it << ")it->fd: " << it->fd << " | data.sock_fd: " << data.sock_fd << " | end(" << &end << ")");
		if (it->revents == 0)
			continue;
		else
		{
			if (it->fd == data.sock_fd)
			{
				COUT(WHITE, "listening socket is readable");
				while (1)
				{
					if (new_connection(data) == -1)
						break;
				}
				end = data.poll_fds.end();
			}
			else
			{
				COUT(WHITE, it->fd << " is readable");
				io_loop(data, it);
			}
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
		if (poll_setup(data) == 1)
			return (1);
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
	// TESTS SOCKET
	if ((data.sock_fd = socket(data.bind_addr->ai_family,
							   data.bind_addr->ai_socktype, data.bind_addr->ai_protocol)) == -1)
	{
		put_error("socket()");
		return (1);
	}
	COUT(BLUE, data.sock_fd);
	add_fd(data, data.sock_fd);
	if (bind(data.sock_fd, data.bind_addr->ai_addr, data.bind_addr->ai_addrlen) == -1)
	{
		put_error("bind()");
		return (1);
	}

	if (listen(data.sock_fd, BACKLOG) == -1)
	{
		put_error("listen()");
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