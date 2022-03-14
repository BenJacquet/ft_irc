/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:36:03 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/14 11:58:09 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief function that counts how many bytes are stored in str
 * 
 * @param str string to analyze
 * @return amount of bytes stores in str
 */
int ft_strlen(const char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return (i);
}

/**
 * @brief a bouger dans user_managemnt
 * 
 */

Users& find_client(t_data &data, int fd)
{
	v_Users::iterator it = data.users.begin();
	v_Users::iterator ite = data.users.end();
	for(; it != ite; it++)
	{
		if (it->getFd() == fd)
			return (*it);
	}
	//COUT(WHITE, "end(" << &(*ite) << ") - " << "(" << &(*it) << ") - " << "FIND CLIENT fd to look for=" << fd << " ||| it->fd=" << it->getFd() << " ||| size of user=" << data.users.size());
	return (*it);
}