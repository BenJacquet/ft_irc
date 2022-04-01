/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_management.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:55:09 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 17:47:12 by jabenjam         ###   ########.fr       */
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
