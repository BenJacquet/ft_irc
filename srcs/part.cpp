/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:50:06 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/23 14:05:16 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	part_parsing(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(cmd.getPayload());
	v_Chan::iterator it = data.chans.begin();
	for (v_Chan::iterator ite = data.chans.end();
		it != ite && it->getTopic() != args[1]; it++)
		;
	if (it == data.chans.end())
		COUT(RED, args[1] << "cannot be quit! (not find ther channel)");
	else
	{
		it->rmusers(*(cmd.getSender()));
		std::string to_send = ":" + cmd.getSender()->getFull_id() + " PART " + args[1];
		send_packets(cmd.getSender()->getFd(), to_send);
	}
}