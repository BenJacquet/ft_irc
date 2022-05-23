/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:07:42 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/21 11:09:20 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	kick_parsing(t_data &data, Message &cmd)
{
	Users &sender = *cmd.getSender();
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args.size() < 4)
	{
		send_packets(sender, create_reply(&sender, 461) + ERR_NEEDMOREPARAMS(args[0]));
		return ;
	}
	std::string content = args[3];
	for (size_t i = 4; i < args.size() ; i++)
		content += " " + args[i];
	Chan *new_chan = is_chan_exist(data, args[1]);
	d_Users::iterator target = find_client_nick(data, args[2]);
	if (new_chan == NULL)
	{
		send_packets(sender, create_reply(&sender, 403) + ERR_NOSUCHCHANNEL(args[1]));
		return ;
	}
	if (target == data.users.end())
	{
		send_packets(sender, create_reply(&sender, 441) + ERR_USERNOTINCHANNEL(args[2] + " " + new_chan->getName()));
		return ;
	}
	if (sender.getMode().find("oO") == std::string::npos &&\
		sender != new_chan->getCreator())
	{
		send_packets(sender, create_reply(&sender, 482) + ERR_NOPRIVILEGE());
		return ;
	}
	v_Users_ptr vect = new_chan->getUsers();
	v_Users_ptr::iterator it = vect.begin();
	for (v_Users_ptr::iterator ite = vect.end(); it != ite && **it != *target; it++)
		;
	if (it == vect.end())
	{
		send_packets(sender, create_reply(&sender, 441) + ERR_USERNOTINCHANNEL(args[2] + " " + new_chan->getName()));
		return ;
	}
	if (new_chan->rmusers(&(*target)))
	{
		it = vect.begin();
		for (v_Users_ptr::iterator ite = vect.end(); it != ite; it++)
			send_packets(**it, ":" + sender.getFull_id() + " KICK " + args[1] + " "\
			+ args[2] + content);
		send_packets(*target, ":" + sender.getFull_id() + " KICK " + args[1] + " "\
			+ args[2] + content);
		send_packets(*target, ":" + target->getFull_id() + " PART " + new_chan->getName());
	}
}
