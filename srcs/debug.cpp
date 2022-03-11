/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:45:28 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/11 11:56:06 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	print_pollfd(t_data &data)
{
	v_pollfds::iterator it = data.poll_fds.begin();
	v_pollfds::iterator end = data.poll_fds.end();

	COUT(YELLOW, "pollfd content:");
	for (; it != end; it++)
		COUT(YELLOW, "(" << &(*it) << ") - " << it->fd);
}