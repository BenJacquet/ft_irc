/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:45:28 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/30 07:46:48 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	print_pollfd(t_data &data)
{
	v_pollfds::iterator it = data.poll_fds.begin();
	v_pollfds::iterator end = data.poll_fds.end();

	COUT(MAGENTA, "pollfd content:");
	COUT(MAGENTA, "Contains " << data.poll_fds.size() << (data.poll_fds.size() <= 1 ? " fd" : " fds"));
	COUT(MAGENTA, "Begin is (" << &(*it) << ") - " << "End is (" << &(*end) << ")");
	for (; it != end; it++)
		COUT(MAGENTA, "(" << &(*it) << ") - " << it->fd);
}

void	print_users(t_data &data)
{
	v_Users::iterator it = data.users.begin();
	v_Users::iterator end = data.users.end();
	COUT(YELLOW, "Users vector:");
	COUT(YELLOW, "Contains " << data.users.size() << (data.users.size() <= 1 ? " user" : " users"));
	COUT(YELLOW, "Begin is (" << &(*it) << ") - " << "End is (" << &(*end) << ")");
	for (int z = 0; it != end; it++, z++)
		COUT(YELLOW, "(" << &(*it) << ") - " << z
		<< *it);
}