/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/16 17:38:50 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	command_nick(t_data &data, Message &cmd) // author thoberth
{
	(void)data;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	cmd.getSender()->setReg_status(1);
	cmd.getSender()->setNick_name(args[1]);
	// edit nick of sender
}

void	command_user(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args.size() < 5)
		return;
	cmd.getSender()->setReg_status(2);
	cmd.getSender()->setUser_name(args[2]);
	cmd.getSender()->setHostname(args[3]);
	cmd.getSender()->setReal_name(args[4] + (args.size() == 6 ? " " + args[5] : ""));
	cmd.getSender()->setFull_id(args[1] + "!" + args[2] + "@" + args[3]);
	registration(data, *cmd.getSender());
	// edit real_name of sender;
}

void	command_pass(t_data &data, Message &cmd)
{
	registration(data, *cmd.getSender());
	cmd.getSender()->setReg_status(3);
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