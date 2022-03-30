/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/30 07:46:23 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

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

void	command_nick(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());
	std::string nick = args[1];

	try
	{
		sender->setNick_name(nick);
		authenticate_user(data, sender, nick);
		sender->setIn_use(false);
		if (sender->getReal_name().empty() == false)
		{
			sender->setFull_id(nick + "!" + sender->getUser_name() + "@" + sender->getHost_name());
			if (sender->getOnline() == false)
				registration(data, sender);
			send_packets(*sender, UPDATE_NICK(nick + "!" + sender->getUser_name() + "@" + sender->getHost_name(), nick));
		}
	}
	catch (const std::exception &e)
	{
		send_packets(*sender, create_reply(data, sender, 433, nick));
		sender->setIn_use(true);
	}
	sender->setReg_status((sender->getNick_name().empty() == true ? 1 : sender->getReg_status()));
	// edit nick of sender
}

void	command_user(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	if (args.size() < 5)
		return;
	sender->setReg_status((sender->getUser_name().empty() == true ? 2 : sender->getReg_status()));
	sender->setReg_status((sender->getPw().empty() == true ? sender->getReg_status() : 3));
	sender->setUser_name(args[2]);
	sender->setHostname(args[3]);
	sender->setReal_name((&args[4][1] + (args.size() == 6 ? " " + args[5] : "")));
	sender->setFull_id(sender->getNick_name() + "!" + args[2] + "@" + args[3]);
	if (sender->getOnline() == false && sender->getIn_use() == false)
		registration(data, sender);
	// edit real_name of sender;
}

void	command_pass(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	sender->setReg_status(3);
	if (args.size() > 1 && args[1].empty() == false)
	{
		sender->setPw(encrypt_data(data.salt, args[1]));
	}
	// check user password and authenticate if valid
}

void	command_ping(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();

	std::string pong = cmd.getPayload().replace(0, 4, "PONG");
	send_packets(*sender, pong);
	// replies to ping messages from clients
}

void	command_pong(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());


	if (args.size() >= 2 && args[1].compare(sender->getHost_name()) == 0)
	{
		COUT(GREEN, "good PONG");
		sender->setLast_ping(time(NULL));
		// reset le timer pour cette connexion;
	}
	else
		COUT(RED, "bad PONG");
	// checks pong messages from clients
}

void	command_die(t_data &data, Message &cmd)
{
	(void)data;
	(void)cmd;
	exit(1);
	// checks for privileges and kills server
}

void	initialize_command_map(t_data &data)
{
	data.commands.clear();
	data.commands.insert(p_Command("NICK", &command_nick));
	data.commands.insert(p_Command("USER", &command_user));
	data.commands.insert(p_Command("PASS", &command_pass));
	data.commands.insert(p_Command("PING", &command_ping));
	data.commands.insert(p_Command("PONG", &command_pong));
	data.commands.insert(p_Command("PRIVMSG", &command_privmsg));
	data.commands.insert(p_Command("die", &command_die));
	data.commands.insert(p_Command("JOIN", &join_parsing));
	data.commands.insert(p_Command("PART", &part_parsing));
	data.commands.insert(p_Command("WHO", &who_command_parsing));
	data.commands.insert(p_Command("MODE", &mode_parsing));
	data.commands.insert(p_Command("AWAY", &away_parsing));
}