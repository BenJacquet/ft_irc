/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/01 13:03:07 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

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

void	command_die(t_data &data, Message &cmd) // AJOUTER CHECK DES MODES
{
	(void)data;
	(void)cmd;
	Users *sender = cmd.getSender();

	if (sender->getMode().find_first_of("o", 0) != std::string::npos)
		server_shutdown();
	// checks for privileges and kills server
}

void	initialize_command_map(t_data &data)
{
	data.commands.clear();
	data.commands.insert(p_Command("NICK", &command_nick));
	data.commands.insert(p_Command("USER", &command_user));
	data.commands.insert(p_Command("PASS", &command_pass));
	data.commands.insert(p_Command("PING", &command_ping));
	data.commands.insert(p_Command("PRIVMSG", &command_privmsg));
	data.commands.insert(p_Command("die", &command_die));
	data.commands.insert(p_Command("JOIN", &join_parsing));
	data.commands.insert(p_Command("PART", &part_parsing));
	data.commands.insert(p_Command("WHO", &who_command_parsing));
	data.commands.insert(p_Command("MODE", &mode_parsing));
	data.commands.insert(p_Command("AWAY", &away_parsing));
}