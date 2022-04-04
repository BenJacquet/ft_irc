/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:36:03 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/04 11:53:31 by jabenjam         ###   ########.fr       */
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
 * @brief Creates the ipv6 mapped address string from a sockaddr_in6
 * 
 * @param address 
 * @return std::string 
 */
std::string get_ip_string(sockaddr_in6 address)
{
	char buffer[46];
	inet_ntop(address.sin6_family, &address.sin6_addr, buffer, 46);
	return (std::string(buffer));
}

/**
 * @brief Checks if a channel exists
 * 
 * @param data 
 * @param args 
 * @return Chan* 
 */
Chan*		is_chan_exist(t_data &data, std::string args)
{
	v_Chan::iterator ite = data.chans.end();
	for (v_Chan::iterator it = data.chans.begin(); it != ite ; it++)
	{
		if (it->getTopic() == args)
			return &(*it);
	}
	return NULL;
}
