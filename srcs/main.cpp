/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:20:43 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/30 07:50:28 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

int main(int ac, char **av)
{
	t_data data;

	if (parse_arguments(ac, av, data) != 0 || addrinfo_setup(data, av) != 0 || server_setup(data) != 0)
		return (1);
	COUT(L_CYAN, ASCII_HEADER);
	COUT(L_CYAN, "Log File: " << MAGENTA << "log.txt" << RESET);
	COUT(L_CYAN, "Listening port: " << MAGENTA << data.port << RESET);
	server_loop(data);
	return (0);
}
