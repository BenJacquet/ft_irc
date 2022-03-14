/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:38:16 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/14 12:07:47 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	registration(t_data &data, Users *client)
{
	// std::string host = "localhost";
	// std::string nick = "jabenjam";
	// std::string user = "jabenjam!jabenjam@localhost";
	send_packets(client->getFd(), RPL_WELCOME(client->getHost_name(), client->getNick_name(),\
		client->getFull_id()));
	add_fd(data, client->getFd());
}

std::vector<std::string>	parse_line(const std::string &line)
{
	std::istringstream	line_stream(line);

	std::vector<std::string> words;
	for (int z = 0; std::getline(line_stream, words[z], ' '); z++)
		COUT(CYAN, "words[" << z << "] - " << words[z]);
	return (words);
}

void	command_parsing(t_data &data, Users *client, char buffer[BUFFERSIZE])
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