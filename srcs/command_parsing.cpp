/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:38:16 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/02 12:39:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

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