/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:36:03 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/30 07:54:45 by jabenjam         ###   ########.fr       */
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

v_Users::iterator find_client_fd(t_data &data, int fd)
{
	v_Users::iterator it = data.users.begin();
	v_Users::iterator ite = data.users.end();
	for(; it != ite; it++)
	{
		if (it->getFd() == fd)
			return (it);
	}
	//COUT(WHITE, "end(" << &(*ite) << ") - " << "(" << &(*it) << ") - " << "FIND CLIENT fd to look for=" << fd << " ||| it->fd=" << it->getFd() << " ||| size of user=" << data.users.size());
	return (it);
}

v_Users::iterator find_client_uid(t_data &data, unsigned int uid)
{
	v_Users::iterator it = data.users.begin();
	v_Users::iterator ite = data.users.end();
	for(; it != ite; it++)
	{
		if (it->getUid() == uid)
			return (it);
	}
	return (it);
}

v_Users::iterator find_client_nick(t_data &data, std::string nick)
{
	v_Users::iterator it = data.users.begin();
	v_Users::iterator ite = data.users.end();
	for(; it != ite; it++)
	{
		if (it->getNick_name().compare(nick) == 0)
			return (it);
	}
	return (it);
}

std::string get_ip_string(sockaddr_in6 address)
{
	char buffer[46];
	inet_ntop(address.sin6_family, &address.sin6_addr, buffer, 46);
	return (std::string(buffer));
}

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

bool	check_timeout(t_data &data, Users &user)
{
	time_t time_now = time(NULL);

	if ((time_now - user.getLast_ping()) > TIMEOUT)
	{
		send_packets(user, "QUIT\r\n");
		disconnect_user(data, user);
		return (true);
	}
	return (false);
}