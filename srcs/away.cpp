/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 06:44:58 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/30 07:08:02 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

void	away_parsing(t_data &data, Message &cmd)
{
	Chan *chan;
	std::vector<std::string> args = parse_line(cmd.getPayload());

	if ((chan = is_chan_exist(data, args[1])) != NULL)
	{
		if (chan->getMode().find("a") != std::string::npos)
		{
			chan->setMode(chan->getMode().erase(chan->getMode().find("a"), 1));
		}
		else
		{
			chan->setMode(chan->getMode() + "a");
		}
	}
}