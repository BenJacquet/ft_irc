/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/17 10:12:26 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	command_nick(t_data &data, Message &cmd)
{
	(void)data;
	Users	*sender = cmd.getSender();
	std::string charset = "0123456789";
	std::vector<std::string> args = parse_line(cmd.getPayload());
	std::string nick = args[1];

	// for (int i = 0; find_client_nick(data, nick) != data.users.end(); i++)
	// {
	// 	if (i > 9)
	// 		i = 0;
	// 	tmp = nick + charset[i];
	// }
	// while (find_client_nick(data, nick) != data.users.end())
		// nick = alter_nick(nick);
	sender->setReg_status((sender->getNick_name().empty() == true ? 1 : sender->getReg_status()));
	sender->setNick_name(nick);
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
	sender->setFull_id(args[1] + "!" + args[2] + "@" + args[3]);
	registration(data, *sender);
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

// void	command_privmsg(t_data &data, Message &cmd)
// {
// 	(void)data;
// 	(void)cmd;
// 	(void)
// 	// checks for user and 
// }

void	initialize_command_map(t_data &data)
{
	data.commands.clear();
	data.commands.insert(p_Command("NICK", &command_nick));
	data.commands.insert(p_Command("USER", &command_user));
	data.commands.insert(p_Command("PASS", &command_pass));
	data.commands.insert(p_Command("PING", &command_ping));
	// data.commands.insert(p_Command("PRIVMSG", &command_privmsg));
	data.commands.insert(p_Command("die", &command_die));
	data.commands.insert(p_Command("JOIN", &join_parsing));
}