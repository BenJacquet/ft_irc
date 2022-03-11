/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/11 13:57:43 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	command_nick(t_data &data, Message &cmd)
{
	(void)data;
	(void)cmd;
	// send_packets(cmd.getSender(), cmd.getPayload());
	// registration(data, cmd.getSender());
	// edit nick of sender
}

void	command_user(t_data &data, Message &cmd)
{
	registration(data, cmd.getSender());
	// edit real_name of sender;
}

void	command_pass(t_data &data, Message &cmd)
{
	registration(data, cmd.getSender());
	// check user password and authenticate if valid
}

void	command_ping(t_data &data, Message &cmd)
{
	(void)data;
	send_packets(cmd.getSender(), "localhost");
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
}