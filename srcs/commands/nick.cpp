/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:03:39 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/02 13:03:46 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

/**
 * @brief checks if nick contains illegal characters or is too long
 * 
 * @param data 
 * @param user 
 * @param nick 
 */
void	check_nick(t_data &data, Users &user, std::string nick)
{
	size_t found = nick.find_first_not_of(NICK_CHARSET(), 0);
	if (nick.length() > 9 || found != std::string::npos)
	{
		send_packets(user, create_reply(data, &user, 432, nick));
		COUT(RED, "character is not allowed=[" << static_cast<int>(nick[found]) << "]");
	}
}

/**
 * @brief authenticates the user sets a variable containing the old connection to replace
 * 
 * @param data 
 * @param client 
 * @param nick 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Parses the NICK command received, checks and authenticates the user
 * 
 * @param data 
 * @param cmd 
 */
void	command_nick(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());
	std::string nick;

	if (args.size() == 1 || args[1].empty() == true)
	{
		send_packets(*sender, create_reply(data, sender, 431, ""));
		nick = "";
	}
	else
		nick = args[1];
	check_nick(data, *sender, nick);
	try
	{
		std::string old_nick(sender->getNick_name());
		sender->setNick_name(nick);
		authenticate_user(data, sender, nick);
		sender->setIn_use(false);
		if (sender->getReal_name().empty() == false)
		{
			sender->setFull_id(nick + "!" + sender->getUser_name() + "@" + sender->getHost_name());
			if (sender->getOnline() == false)
				registration(data, sender);
			send_packets(*sender, UPDATE_NICK(old_nick + "!" + sender->getUser_name() + "@" + sender->getHost_name(), nick));
		}
	}
	catch (const std::exception &e)
	{
		send_packets(*sender, create_reply(data, sender, 433, nick));
		sender->setIn_use(true);
	}
	sender->setReg_status((sender->getNick_name().empty() == true ? 1 : sender->getReg_status()));
}