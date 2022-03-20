/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:14:21 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/20 21:47:57 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

Chan*		is_chan_exist(t_data &data, std::string args)
{
	v_Chan::iterator ite = data.chans.end();
	for (v_Chan::iterator it = data.chans.begin(); it != ite ; it++)
	{
		if (it->getTopic() == args)
			return &(*it);
	}
	return NULL;
}

void		join_parsing(t_data &data, Message &cmd)
{
	Chan *new_chan;
	std::string chan;
	std::string pw;
	size_t pos;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	for(size_t i=0; i < args.size(); i++)
		COUT(L_BLUE, "i = " << i << " " << args[i]);
	while ((pos = args[1].find(',')) != std::string::npos)
	{
		COUT(L_BLUE, "testyest\n");
		chan.assign(args[1], 0, pos);
		args[1].erase(0, pos + 1);
		while (args.size() > 2 && (pos = args[2].find(',')) != std::string::npos)
		{
			pw.assign(args[2], 0, pos);
			args[2].erase(0, pos + 1);
		}
		if ((new_chan = is_chan_exist(data, chan)) != NULL)
		{
			if (new_chan->addusers(*(cmd.getSender())))
				COUT(L_BLUE, cmd.getSender()->getNick_name() << " has been added to " << chan);
			else
				COUT(L_BLUE, cmd.getSender()->getNick_name() << " cannot be add to " << chan);
		}
		else
			join(data, *(cmd.getSender()), chan);
	}
	chan = args[1];
	if ((new_chan = is_chan_exist(data, chan)) != NULL)
	{
		if (new_chan->addusers(*(cmd.getSender())))
			COUT(L_BLUE, cmd.getSender()->getNick_name() << "has been added to " << chan);
		else
			COUT(L_BLUE, cmd.getSender()->getNick_name() << " cannot be add to " << chan);
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
void		join(t_data &data, Users & creator, std::string name_chan,
	std::string mdp_tojoin, bool isprivate)
{
	std::string full_msg = std::string(":") + creator.getFull_id() + std::string(" JOIN ") + name_chan;
	std::string RPL_353 = std::string(":") + creator.getFull_id() + std::string(" 353 ") + creator.getNick_name() +\
		std::string(" = ") + name_chan + std::string(" :@") + creator.getNick_name();
	std::string RPL_366 = std::string(":") + creator.getFull_id() + std::string(" 366 ") + creator.getNick_name() + std::string(" ") + name_chan + std::string(" :End of /NAMES list");
	data.chans.push_back(Chan(creator, name_chan, mdp_tojoin, isprivate));
	// send_packets(creator.getFd(), RPL_353 );
	// send_packets(creator.getFd(), RPL_366 );
	// send_packets(creator.getFd(), full_msg);
	std::string test("blabla");
	COUT(WHITE, "heasdfasdfy" + test + "|tdsafasdfasdt|");
}
