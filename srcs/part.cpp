/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:50:06 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/18 11:48:38 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	part_parsing(t_data &data, Message &cmd)
{
	(void)data;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	std::string to_send = ":" + cmd.getSender()->getFull_id() + " PART " + args[1] + " has left!";
	std::cout << to_send << '\n';
	send_packets(cmd.getSender()->getFd(), to_send);
}