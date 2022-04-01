/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_management.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:55:09 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 13:20:49 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	registration(t_data &data, Users *client)
{
	send_packets(*client, create_reply(data, client, 001 , ""));
	client->setOnline(true);
}

void	replace_user(t_data &data, Users &user)
{
	int	to_replace = user.getAuthenticated();

	if (to_replace != 0)
	{
		v_Users::iterator authentified = find_client_uid(data, to_replace);
		if (authentified != data.users.end())
		{
			data.users.erase(authentified);
		}
	}
	user.connect(user);
}

void	disconnect_user(t_data &data, Users &client)
{
	v_Users::iterator it = data.users.begin();
	v_Users::iterator end = data.users.end();

	put_disconnection(client.getFd());
	remove_fd(data, client.getFd());
	client.disconnect();
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

void	check_nick(t_data &data, std::string &nick)
{
	(void)data;
	(void)nick;
	// Verifier si nick < 9 chars
	// Verifier si chars interdits
}

bool	authenticate_user(t_data &data, Users *client, std::string nick)
{
	v_Users::iterator found_reg = find_client_nick(data, nick);
	v_Users::iterator found_unreg = find_client_fd(data, client->getFd());

	if (found_reg != data.users.end())
	{
		if (found_reg == found_unreg)
			return (true);
		if (found_reg->getPw() == client->getPw() && found_reg->getOnline() == false)
		{
			found_unreg->setAuthenticated(found_reg->getUid());
			return (true);
		}
		throw std::exception();
	}
	return (false);
}