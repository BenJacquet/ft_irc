/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:24:44 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/21 10:17:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief finds the fd received as argument in the pollfd vector
 * 
 * @param data
 * @param fd fd to find
 * @return iterator to found occurence or iterator to end if not found
 */
v_pollfds::iterator find_pollfd_fd(t_data &data, int fd)
{
	v_pollfds::iterator it = data.poll_fds.begin();
	v_pollfds::iterator end = data.poll_fds.end();

	for (; it != end; it++)
	{
		if (it->fd == fd)
			return (it);
	}
	return (end);
}
/**
 * @brief removed the fd from the pollfd vector
 * 
 * @param data
 * @param fd fd to remove
 */
void remove_fd(t_data &data, int fd)
{
	// v_pollfds::iterator end = data.poll_fds.end();
	v_pollfds::iterator found = find_pollfd_fd(data, fd);

	// COUT(MAGENTA, "end=" << &(*end) << "found=" << &(*found));
	COUT(RED, "removed descriptor " << fd << " from pollfd vector ");
	close(fd); // check si interdit ou non
	data.poll_fds.erase(found);
}

/**
 * @brief adds the fd to the pollfd vector
 * 
 * @param data
 * @param fd fd to add
 */
void add_fd(t_data &data, int fd)
{
	v_pollfds::iterator end = data.poll_fds.end();
	v_pollfds::iterator found = find_pollfd_fd(data, fd);
	struct pollfd poll;

	poll.fd = fd;
	poll.events = (POLLIN);
	poll.revents = 0;
	if (found != end)
		return;
	fcntl(fd, F_SETFL, O_NONBLOCK);
	data.poll_fds.push_back(poll);
	//COUT(CYAN, "added descriptor " << poll.fd << " to pollfd vector ");
}

/**
 * @brief accepts new connections and adds them to the pollfd vector
 * 
 * @param data
 * @return the new client fd in case of valid connection and
 * 			-1 in case of accept() malfunction
 */
int new_connection(t_data &data)
{
	struct sockaddr_in6	client_sock;
	socklen_t			size = sizeof(struct sockaddr_storage);
	int					client_fd = accept(data.sock_fd, reinterpret_cast<struct sockaddr *>(&client_sock), &size);
	if (client_fd < 1)
	{
		CERR(YELLOW, "accept()");
		return (-1);
	}
	data.users.push_back(Users(client_fd, client_sock, data));
	add_fd(data, client_fd);
	return (client_fd);
}