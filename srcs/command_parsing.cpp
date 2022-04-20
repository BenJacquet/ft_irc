/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:38:16 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/20 12:11:12 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief Splits a line into a vector of arguments
 * 
 * @param line 
 * @return std::vector<std::string> 
 */
std::vector<std::string>	parse_line(const std::string &line)
{
	std::istringstream	line_stream(line);

	std::vector<std::string> words;
	std::string buffer;
	int	z = 0;
	for (; std::getline(line_stream, buffer, ' '); z++)
	{
		remove_carriage(buffer);
		words.push_back(buffer);
		buffer.clear();
	}
	return (words);
}

/**
 * @brief Parses the commands received into a TCP/IP packet
 * 
 * @param data 
 * @param client 
 * @param buffer 
 */
void	command_parsing(t_data &data, Users &client, std::string buffer)
{
	std::string line;
	std::istringstream buffer_stream(buffer);
	m_Commands::iterator it = data.commands.begin();
	m_Commands::iterator end = data.commands.end();
	while (1)
	{
		std::getline(buffer_stream, line, '\n');
		Message	cmd(&client, line);
		if (line.empty() == true)
			break;
		if (line.find("CAP LS", 0) == 0)
			continue;
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