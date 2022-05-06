/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/06 13:50:40 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief Initializes the command map with strings and function pointers to corresponding commands
 * 
 * @param data 
 */
void	initialize_command_map(t_data &data)
{
	data.commands.clear();
	data.commands.insert(p_Command("NICK", &command_nick));
	data.commands.insert(p_Command("USER", &command_user));
	data.commands.insert(p_Command("PASS", &command_pass));
	data.commands.insert(p_Command("PING", &command_ping));
	data.commands.insert(p_Command("OPER", &command_oper));
	data.commands.insert(p_Command("PRIVMSG", &command_privmsg));
	data.commands.insert(p_Command("die", &command_die));
	data.commands.insert(p_Command("JOIN", &join_parsing));
	data.commands.insert(p_Command("PART", &part_parsing));
	data.commands.insert(p_Command("MODE", &mode_parsing));
	data.commands.insert(p_Command("AWAY", &away_parsing));
	data.commands.insert(p_Command("KICK", &kick_parsing));
}