/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/25 13:41:36 by jabenjam         ###   ########.fr       */
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
		else if (found_reg->getPw() == client->getPw() && found_reg->getOnline() == false)
		{
			found_reg->connect(*found_unreg);
			data.users.erase(found_unreg);
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
		authenticate_user(data, sender, nick);
		sender->setNick_name(nick);
		sender->setIn_use(false);
		if (sender->getReal_name().empty() == false)
		{
			sender->setFull_id(nick + "!" + sender->getUser_name() + "@" + sender->getHost_name());
			COUT(RED, "UPDATED FULLID");
			send_packets(sender->getFd(), UPDATE_NICK(sender->getFull_id(), nick));
			COUT(GREEN, "REGISTERED IN NICK");
			registration(data, *sender);
		}
	}
	catch (const std::exception &e)
	{
		send_packets(sender->getFd(), create_reply(data, sender, 433, nick));
		sender->setIn_use(true);
	}
	sender->setReg_status((sender->getNick_name().empty() == true ? 1 : sender->getReg_status()));
	// edit nick of sender
}

void	command_user(t_data &data, Message &cmd)
{
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
	if (sender->getIn_use() == false)
	{
		COUT(GREEN, "REGISTERED IN USER");
		registration(data, *sender);
	}
	// edit real_name of sender;
}

void	command_pass(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());

	sender->setReg_status(3);
	sender->setPw(args[1]);
	// check user password and authenticate if valid
}

void	command_ping(t_data &data, Message &cmd)
{
	(void)data;
	send_packets(cmd.getSender()->getFd(), "localhost");
	// check user password and authenticate if valid
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
	data.commands.insert(p_Command("PRIVMSG", &command_privmsg));
	data.commands.insert(p_Command("die", &command_die));
	data.commands.insert(p_Command("JOIN", &join_parsing));
	data.commands.insert(p_Command("PART", &part_parsing));
}