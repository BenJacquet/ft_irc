/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:45:28 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/28 13:04:39 by jabenjam         ###   ########.fr       */
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
		<< std::endl << "- Nick:" << it->getNick_name()
		<< std::endl << "- Real Name:" << it->getReal_name()
		<< std::endl << "- Hostname:" << it->getHost_name()
		<< std::endl << "- Full id:" << it->getFull_id()
		<< std::endl << "- Password:" << it->getPw()
		<< std::endl << "- Fd:" << it->getFd()
		<< std::endl << "- Online:" << it->getOnline()
		<< std::endl << "- Reg Status:" << it->getReg_status()
		<< std::endl << "- Authenticated:" << it->getAuthenticated()
		<< std::endl << "- Uid:" << it->getUid()
		<< std::endl << "-------------");
}