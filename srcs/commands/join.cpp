/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:14:21 by thoberth          #+#    #+#             */
/*   Updated: 2022/04/04 15:42:59 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void		join_parsing(t_data &data, Message &cmd)
{
	Chan *new_chan;
	std::string chan;
	size_t pos;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	while ((pos = args[1].find(',')) != std::string::npos)
	{
		chan.assign(args[1], 0, pos);
		args[1].erase(0, pos + 1);
		if ((new_chan = is_chan_exist(data, chan)) != NULL)
		{
			if (new_chan->addusers(*(cmd.getSender())))
				join_msg(*(cmd.getSender()), *new_chan, false);
			else
				CERR(L_BLUE, cmd.getSender()->getNick_name() << " cannot be add to " << chan);
		}
		else
			join(data, *(cmd.getSender()), chan);
	}
	chan = args[1];
	if ((new_chan = is_chan_exist(data, chan)) != NULL)
	{
		if (new_chan->addusers(*(cmd.getSender())))
			join_msg(*(cmd.getSender()), *new_chan, false);
		else
			CERR(L_BLUE, cmd.getSender()->getNick_name() << " cannot be add to " << chan);
	}
	else
		join(data, *(cmd.getSender()), chan);
}

/**
 * @brief /join if name_Chan don't exist (here) creator create name_Chan
 * 
 * @param data struct who store everything
 * @param creator creator of the Chan
 * @param name_Chan name of the Chan
 * @param mdp_tojoin the password if isprivate is true
 * @param isprivate false if no passw to set else true
 */
void		join(t_data &data, Users & creator, std::string name_chan)
{
	data.chans.push_back(Chan(creator, name_chan));
	join_msg(creator, data.chans.back(), true);
}

void		join_msg(Users &to_add, Chan &chan, bool isnewone)
{
	if (!isnewone)
	{
		std::string s;
		v_Users vect = chan.getUsers();
		RPL_353_366(to_add, chan);
		for (v_Users::iterator it = vect.begin(), ite = vect.end();
			it != ite; it++)
		{
			s = ":" + to_add.getFull_id() + " JOIN :" + chan.getTopic();
			send_packets(*it, s);
		}
	}
	else
	{
		RPL_353_366(to_add, chan);
		std::string full_msg = ":" + to_add.getFull_id() + " JOIN :" + chan.getTopic();
		send_packets(to_add, full_msg);
	}
}

void		RPL_353_366(Users &usr, Chan &chan)
{
	std::string rpl_353 =  ":" + usr.getFull_id() + " 353 " + usr.getNick_name() + " = " + chan.getTopic() + " :@";
	v_Users vect = chan.getUsers();
	for (v_Users::iterator it = vect.begin(), ite = vect.end();
		it != ite; it++)
		rpl_353 += it->getNick_name() + " ";
	send_packets(usr, rpl_353);
	std::string rpl_366 = ":" + usr.getFull_id() + " 366 " + usr.getNick_name() + " " + chan.getTopic() + " :End of /NAMES list";
	send_packets(usr, rpl_366);
}
