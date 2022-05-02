/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:50:06 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/02 13:12:26 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	part_parsing(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(cmd.getPayload());
	Chan *chan = is_chan_exist(data, args[1]);
	if (chan == NULL)
	{
		send_packets(*cmd.getSender(), create_reply(data, cmd.getSender(), 403, args[1]));
		return ;
	}
	v_Users vect = chan->getUsers();
	v_Users::iterator it = vect.begin();
	for (v_Users::iterator ite = vect.end(); it != ite && *it != *cmd.getSender(); it++)
		;
	if (it == vect.end())
	{
		send_packets(*cmd.getSender(), create_reply(data, cmd.getSender(), 442, chan->getName()));
		return ;
	}
	std::string to_send = ":" + cmd.getSender()->getFull_id() + " PART " + args[1];
	for (v_Users::iterator it2 = vect.begin(),
		ite2 = vect.end(); it2 != ite2; it2++)
		send_packets(*it2, to_send);
	chan->rmusers(*(cmd.getSender()));
}