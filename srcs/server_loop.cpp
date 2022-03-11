/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:34:54 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/11 17:45:47 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

struct addrinfo	*listen_socket;
int 			listen_fd;

/**
 * @brief polls all fds to check if one had any expected event
 * and manages new connections, i/o operations
 * 
 * @param data 
 * @return 1 if poll() malfunctionned or if poll() timed out
 */
int poll_setup(t_data &data)
{
	int poll_r = poll(reinterpret_cast<struct pollfd *>(&data.poll_fds[0]), data.poll_fds.size(), data.timeout);
	v_pollfds::iterator it = data.poll_fds.begin();

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
	for (; it != data.poll_fds.end(); it++)
	{
		//COUT(WHITE, "(" << &(*it) << ")it->fd: " << it->fd << " | data.sock_fd: " << data.sock_fd << " | end(" << &(*data.poll_fds.end()) << ")");
		std::cout << "socket_actuel = " << it->fd << std::endl;
		// std::cout << "test 1\n";
		if (it->revents == 0)
			continue;
		else
		{
			// std::cout << "test 2\n";
			if (it->fd == data.sock_fd)
			{
				// std::cout << "test 3\n";
				//COUT(WHITE, "listening socket is readable");
				while (1)
				{
					// std::cout << "test 4\n";
					if (data.poll_fds.size() == data.poll_fds.capacity())
					{
						// std::cout << "test 5\n";
						data.poll_fds.reserve(data.poll_fds.size() * 2);
						it = data.poll_fds.begin();
					}
					if (new_connection(data) == -1)
					{
						// std::cout << "test 6\n";
						break;
					}
				}
			}
			else
			{
				// std::cout << "test 7\n";
				COUT(WHITE, it->fd << " is readable");
				io_loop(data, find_client(data, it->fd));
			}
		}
	}
	return (0);
}

void	handle_signals(int signal)
{
	if (signal == SIGQUIT || signal == SIGINT)
	{
		if (signal == SIGQUIT)
			COUT(WHITE, "\b\bprogram terminated by ctrl-\\");
		else
			COUT(WHITE, "\b\bprogram interrupted by ctrl-c");
		freeaddrinfo(listen_socket);
		close(listen_fd);
		exit(1);
	}
}

void	signal_manager()
{
	signal(SIGQUIT, &handle_signals);
	signal(SIGINT, &handle_signals);
}

/**
 * @brief main server loop
 * 
 * @param data 
 * @return 1 if /quit command is received or poll() return is < 1
 */
int server_loop(t_data &data)
{
	listen_socket = data.bind_addr;
	listen_fd = data.sock_fd;
	initialize_command_map(data);
	data.users.clear();
	while (1)
	{
		signal_manager();
		// if (command_loop(data) == 1)
		// 	return (0);
		if (poll_setup(data) == 1)
			return (1);
	}
	freeaddrinfo(data.bind_addr);
	close(data.sock_fd);
	return (0);
}
