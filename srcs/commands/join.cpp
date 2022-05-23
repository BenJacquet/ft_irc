/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:14:21 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/21 11:01:06 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

int	verif_join(Message &cmd, Chan &new_chan, std::vector<std::string> &args)
{
	std::string pw;
	size_t pos;
	if (new_chan.getMode().find("k") != std::string::npos)
	{
		if (args.size() >= 3 && (pos = args[2].find(',')) != std::string::npos)
		{
			pw.assign(args[2], 0, pos);
			args[2].erase(0, pos + 1);
		}
		else if (args.size() >= 3)
			pw = args[2];
		if (args.size() < 3 || pw != new_chan.getPw())
		{
			send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 475) + ERR_BADCHANNELKEY(new_chan.getName()));
			return 0;
		}
	}
	if (new_chan.getMode().find("l") != std::string::npos &&
		std::atoi(new_chan.getLimit_user().c_str()) <= static_cast<int>(new_chan.getUsers().size()))
	{
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 471) + ERR_CHANNELISFULL(new_chan.getName()));
		return 0;
	}
	return 1;
}

void		join_parsing(t_data &data, Message &cmd)
{
	Chan *new_chan;
	std::string chan;
	size_t pos;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args.size() == 1)
	{
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 461) + ERR_NEEDMOREPARAMS(args[0]));
		return ;
	}
	while ((pos = args[1].find(',')) != std::string::npos)
	{
		// CERR(RED, "args 1 = " << args[1] << " args 2 = " << args[2]);
		chan.assign(args[1], 0, pos);
		args[1].erase(0, pos + 1);
		if ((new_chan = is_chan_exist(data, chan)) != NULL)
		{
			if (new_chan->is_banned(cmd.getSender()))
			{
				send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 474) + ERR_BANNEDFROMCHANNEL(new_chan->getName()));
				return ;
			}
			if (verif_join(cmd, *new_chan, args) && new_chan->addusers(cmd.getSender()))
			{
				join_msg(data, *(cmd.getSender()), *new_chan, false);
				send_packets(*cmd.getSender(), RPL_MODE(cmd.getSender()->getNick_name(), cmd.getSender()->getMode()));
			}
		}
		else
			join(data, *(cmd.getSender()), chan);
	}
	chan = args[1];
	if ((new_chan = is_chan_exist(data, chan)) != NULL)
	{
		if (new_chan->is_banned(cmd.getSender()))
		{
			send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 474) + ERR_BANNEDFROMCHANNEL(new_chan->getName()));
			return ;
		}
		if (verif_join(cmd, *new_chan, args) && new_chan->addusers(cmd.getSender()))
		{
			join_msg(data, *(cmd.getSender()), *new_chan, false);
			send_packets(*cmd.getSender(), RPL_MODE(cmd.getSender()->getNick_name(), cmd.getSender()->getMode()));
		}
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
	data.chans.push_back(Chan(&creator, name_chan));
	join_msg(data, creator, data.chans.back(), true);
	send_packets(creator, RPL_MODE(creator.getNick_name(), creator.getMode()));
}

void		join_msg(t_data &data, Users &to_add, Chan &chan, bool isnewone)
{
	if (!isnewone)
	{
		std::string s;
		v_Users_ptr vect = chan.getUsers();
		RPL_353_366(data, to_add, chan);
		for (v_Users_ptr::iterator it = vect.begin(), ite = vect.end();
			it != ite; it++)
		{
			s = ":" + to_add.getFull_id() + " JOIN :" + chan.getName();
			send_packets(**it, s);
		}
	}
	else
	{
		RPL_353_366(data, to_add, chan);
		std::string full_msg = ":" + to_add.getFull_id() + " JOIN :" + chan.getName();
		send_packets(to_add, full_msg);
	}
}

void		RPL_353_366(t_data &data, Users &usr, Chan &chan)
{
	std::string rpl_353 =  ":" + usr.getFull_id() + " 353 " + usr.getNick_name() + " = " + chan.getName() + " :";
	v_Users_ptr vect = chan.getUsers();
	for (v_Users_ptr::iterator it = vect.begin(), ite = vect.end();
		it != ite; it++)
	{
		if (**it == chan.getCreator() || find_client_nick(data, (*it)->getNick_name())->getMode().find_first_of("oO") != std::string::npos)
			rpl_353 += "@";
		rpl_353 += (*it)->getNick_name() + " ";
	}
	send_packets(usr, rpl_353);
	std::string rpl_366 = ":" + usr.getFull_id() + " 366 " + usr.getNick_name() + " " + chan.getName() + " :End of /NAMES list";
	send_packets(usr, rpl_366);
}
