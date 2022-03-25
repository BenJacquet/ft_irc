/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:50:06 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/25 13:40:14 by thoberth         ###   ########.fr       */
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
		COUT(RED, args[1] << "cannot be quit! (not find this channel)");
	else
	{
		std::string to_send = ":" + cmd.getSender()->getFull_id() + " PART " + args[1];
		v_Users vect = it->getUsers();
		for (v_Users::iterator it2 = vect.begin(),
			ite2 = vect.end(); it2 != ite2; it2++)
			send_packets(it2->getFd(), to_send);
		it->rmusers(*(cmd.getSender()));
	}
}