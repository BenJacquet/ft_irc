/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/09 16:40:58 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	command_nick(t_data &data, Message &cmd)
{
	registration(data, cmd.getSender());
}

void	command_user(t_data &data, Message &cmd)
{
	registration(data, cmd.getSender());
}

void	initialize_command_map(t_data &data)
{
	data.commands.clear();
	data.commands.insert(p_Command("NICK", &command_nick));
	data.commands.insert(p_Command("USER", &command_user));
}