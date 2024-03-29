/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_control.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:41:07 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/09 12:41:53 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief loop function that checks for input on cin, parses it and sends it
 * 		to the adequate function to execute a command
 * 
 * @param data
 * @return int 
 */
int command_loop(t_data &data)
{
	std::string cmd;
	static_cast<void>(data);

	cmd.clear();
	if (std::cin.peek() != EOF)
	{
		std::getline(std::cin, cmd);
		if (cmd.compare("/quit") == 0 || std::cin.eof())
			return (1);
	}
	return (0);
}