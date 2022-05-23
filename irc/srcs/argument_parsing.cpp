/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:31:12 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/04 11:55:34 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief Function that checks wether the string av 
 * 		contains a valid port or not and stores it inside data.port
 * 
 * @param av string containing the port
 * @param data
 * @return true in case the port is valid
 * @return false in case the port is invalid
 */
bool valid_port(std::string av, t_data &data)
{
	if (av.length() > 0)
	{
		if (av.find_first_not_of("0123456789") != std::string::npos)
			return (false);
		int port = atoi(av.c_str());
		if (port < 1024 || port > 65535)
			return (false);
		data.port = static_cast<uint16_t>(port);
		return (true);
	}
	return (false);
}

/**
 * @brief Parses the arguments provided at execution and stores them
 * 
 * @param ac 
 * @param av 
 * @param data 
 * @return int 
 */
int parse_arguments(int ac, char **av, t_data &data)
{
	if (ac != 3)
	{
		put_usage();
		return (1);
	}
	if (valid_port(static_cast<std::string>(av[1]), data) == false)
	{
		put_error("ircserv: invalid port, valid port range is 1025-65535.");
		return (1);
	}
	srand(time(NULL));
	data.salt = random();
	data.password = encrypt_data(data.salt, av[2]);
	return (0);
}