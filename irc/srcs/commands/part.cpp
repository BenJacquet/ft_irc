/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:50:06 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/21 10:54:53 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	part_parsing(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args.size() == 1)
	{
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 461) + ERR_NEEDMOREPARAMS(args[0]));
		return ;
	}
	Chan *chan = is_chan_exist(data, args[1]);
	if (chan == NULL)
	{
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 403) + ERR_NOSUCHCHANNEL(args[1]));
		return ;
	}
	v_Users_ptr vect = chan->getUsers();
	v_Users_ptr::iterator it = vect.begin();
	for (v_Users_ptr::iterator ite = vect.end(); it != ite && *it != cmd.getSender(); it++)
		;
	if (it == vect.end())
	{
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 442) + ERR_NOTONCHANNEL(chan->getName()));
		return ;
	}
	std::string to_send = ":" + cmd.getSender()->getFull_id() + " PART " + args[1];
	for (v_Users_ptr::iterator it2 = vect.begin(),
		ite2 = vect.end(); it2 != ite2; it2++)
		send_packets(**it2, to_send);
	chan->rmusers(cmd.getSender());
}