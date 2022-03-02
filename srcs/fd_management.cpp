/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:24:44 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/02 12:51:20 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

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
	close(fd); // check si interdit ou non
	data.poll_fds.erase(found);
}

void add_fd(t_data &data, int fd)
{
	pollfds::iterator end = data.poll_fds.end();
	pollfds::iterator found = find_fd(data, fd);
	struct pollfd poll;

	poll.fd = fd;
	poll.events = (POLLIN /* | POLLOUT | POLLHUP | POLLNVAL*/);
	poll.revents = 0;
	if (found != end)
		return;
	fcntl(fd, F_SETFL, O_NONBLOCK);
	data.poll_fds.push_back(poll);
	COUT(CYAN, "added descriptor to pollfd vector" << poll.fd);
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