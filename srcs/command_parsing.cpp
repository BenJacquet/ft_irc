/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:38:16 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/11 11:45:22 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	registration(t_data &data, int client_fd)
{
	std::string nick = "jabenjam!jabenjam@localhost";
	send_packets(client_fd, RPL_WELCOME(nick));
	add_fd(data, client_fd);
}


void	command_parsing(t_data &data, int client, char buffer[BUFFERSIZE])
{
	std::string line;
	std::istringstream buffer_stream(buffer);
	m_Commands::iterator it = data.commands.begin();
	m_Commands::iterator end = data.commands.end();
	while (1)
	{
		std::getline(buffer_stream, line, '\n');
		Message	cmd(client, line);
		if (line.empty() == true)
		{
			COUT(YELLOW, "Line is empty");
			break;
		}
		COUT(MAGENTA, "Line extracted = " << line);
		if (line.find("CAP LS", 0) == 0)
		{
			COUT(BLUE, "Found CAP LS");
			continue ;
		}
		for (it = data.commands.begin(); it != end; it++)
		{
			if (line.find(it->first, 0) == 0)
			{
				COUT(BLUE, "Found " << it->first);
				it->second(data, cmd);
			}
		}
		line.clear();
	}
}