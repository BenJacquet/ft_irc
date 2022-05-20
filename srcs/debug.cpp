/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:45:28 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/20 17:06:59 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief prints all the pollfd contained into the vector used by the server
 * 
 * @param data 
 */
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


/**
 * @brief prints all the users contained stored into the server database
 * 
 * @param data 
 */
void	print_users(t_data &data)
{
	d_Users::iterator it = data.users.begin();
	d_Users::iterator end = data.users.end();
	COUT(YELLOW, "Users vector:");
	COUT(YELLOW, "Contains " << data.users.size() << (data.users.size() <= 1 ? " user" : " users"));
	COUT(YELLOW, "Begin is (" << &(*it) << ") - " << "End is (" << &(*end) << ")");
	for (int z = 0; it != end; it++, z++)
		COUT(YELLOW, "(" << &(*it) << ") - " << z
		<< *it);
}