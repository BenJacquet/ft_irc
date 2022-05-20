/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_management.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:55:09 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/20 15:50:13 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	registration(t_data &data, Users *client)
{
	send_packets(*client, create_reply(data, client, 001 , ""));
	send_packets(*client, ASCII_HEADER);
	client->setOnline(true);
}

void	copy_user(Users *lhs, Users *rhs)
{
	lhs->setFd(rhs->getFd());
	lhs->setOnline(rhs->getOnline());
	lhs->setMode(rhs->getMode());
	lhs->setHostname(rhs->getHost_name());
	lhs->setUser_name(rhs->getUser_name());
	lhs->setFull_id(rhs->getFull_id());
	lhs->setReal_name(rhs->getReal_name());
	lhs->setNick_name(rhs->getNick_name());
	lhs->setPw(rhs->getPw());
	lhs->setAway_mode(rhs->getAway_mode());
	lhs->setReg_status(rhs->getReg_status());
	lhs->setIn_use(rhs->getIn_use());
	lhs->setSocket_addr(rhs->getSocket_addr());
}

void	replace_user(t_data &data, Message &cmd)
{
	Users			*user = cmd.getSender();
	unsigned int	to_replace = user->getAuthenticated();

	if (to_replace != 0)
	{
		v_Users::iterator authentified = find_client_uid(data, to_replace);
		Users *updated = &(*authentified);
		if (authentified != data.users.end())
		{
			copy_user(updated, user);
			data.users.erase(find_client_uid(data, user->getUid()));
			user = updated;
			cmd.setSender(updated);
		}
	}
	user->connect(*user);
}

/**
 * @brief Disconnects a user, removes it from the pollfd vector
 * and removed it from database if not authentified
 * 
 * @param data 
 * @param client 
 */
void	disconnect_user(t_data &data, Users &client)
{
	v_Users::iterator it = data.users.begin();
	v_Users::iterator end = data.users.end();
	int	fd = client.getFd();

	client.disconnect();
	remove_fd(data, fd);
	if (client.getReg_status() != 3)
	{
		for (; it != end; it++)
		{
			if (*it == client)
			{
				data.users.erase(it);
				COUT(RED, "removed client (" << &(*it) << ")");
				break;
			}
		}
	}
}

/**
 * @brief Finds a client inside the std::vector<Users> by fd
 * 
 * @param data 
 * @param fd 
 * @return v_Users::iterator 
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
	return (it);
}

/**
 * @brief Finds a client inside the std::vector<Users> by uid
 * 
 * @param data 
 * @param fd 
 * @return v_Users::iterator 
 */
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

/**
 * @brief Finds a client inside the std::vector<Users> by nick
 * 
 * @param data 
 * @param fd 
 * @return v_Users::iterator 
 */
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
