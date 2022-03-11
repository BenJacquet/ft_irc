/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_setup.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:25:04 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/11 13:53:48 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief setup of out listening socket from the hints provided
 * 
 * @param data 
 * @param av array of strings containing port and password
 * @return 0 or 1 if getaddrinfo() malfunctionned
 */
int addrinfo_setup(t_data &data, char **av)
{
	struct addrinfo hints;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
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

/**
 * @brief setup of the server, calls socket(), bind() and listen()
 * 		to prepare the server to be ready to listen
 * 
 * @param data 
 * @return 0 or 1 if socket(), bind() or listen() failed
 */
int server_setup(t_data &data)
{
	data.poll_fds.clear();
	data.timeout = (5 * 60 * 1000);
	// data.users.clear();
	// data.unregistered.clear();
	if ((data.sock_fd = socket(data.bind_addr->ai_family,
								data.bind_addr->ai_socktype, data.bind_addr->ai_protocol)) == -1)
	{
		put_error("socket()");
		return (1);
	}
	int no = 0, yes = 1;
	if (setsockopt(data.sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1
		|| setsockopt(data.sock_fd, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&no, sizeof(no)))
	{
		put_error("setsockopt()");
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
