/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:34:54 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/18 17:12:22 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

struct addrinfo	*g_listen_socket;
int 			g_listen_fd;

/**
 * @brief polls all fds to check if one had any expected event
 * and manages new connections, i/o operations
 * 
 * @param data 
 * @return 1 if poll() malfunctionned or if poll() timed out
 */
int poll_setup(t_data &data)
{
	int poll_r = poll(reinterpret_cast<struct pollfd *>(&data.poll_fds[0]), data.poll_fds.size(), (TIMEOUT * 1000));
	v_pollfds::iterator it = data.poll_fds.begin();
	v_pollfds::iterator end = data.poll_fds.end();

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
		if (it->revents == 0)
		{
			continue;
		}
		else
		{
			if (it->fd == data.sock_fd)
			{
				while (1)
				{
					if (new_connection(data) == -1)
					{
						it = data.poll_fds.begin() + 1;
						end = data.poll_fds.end();
						break;
					}
				}
			}
			else
			{
				v_Users::iterator found = find_client_fd(data, it->fd);
				if (found != data.users.end())
				{
					io_loop(data, *found);
					if (it == (data.poll_fds.end()))
						break;
				}
				if (data.poll_fds.size() < 2)
					break;
			}
		}
	}
	print_pollfd(data);
	print_users(data);
	return (0);
}

/**
 * @brief Signal handler
 * 
 * @param signal 
 */
void	handle_signals(int signal)
{
	if (signal == SIGQUIT || signal == SIGINT)
	{
		if (signal == SIGQUIT)
			COUT(WHITE, "\b\bprogram terminated by ctrl-\\");
		else
			COUT(WHITE, "\b\bprogram interrupted by ctrl-c");
		freeaddrinfo(g_listen_socket);
		close(g_listen_fd);
		server_shutdown();
	}
}

/**
 * @brief Basic signal manager
 * 
 */
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
	g_listen_socket = data.bind_addr;
	g_listen_fd = data.sock_fd;
	initialize_command_map(data);
	while (1)
	{
		signal_manager();
		if (poll_setup(data) == 1)
			return (1);
	}
	freeaddrinfo(data.bind_addr);
	close(data.sock_fd);
	return (0);
}
