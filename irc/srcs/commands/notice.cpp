/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:01:17 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/21 10:54:11 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_irc.hpp"

void	command_notice(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(std::string(cmd.getPayload()));
	d_Users::iterator	new_usr;
	if (args.size() == 1)
	{
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 461) + ERR_NEEDMOREPARAMS(args[0]));
		return ;
	}
	std::string content;
	for(size_t i=2; i < args.size(); i++)
		content += args[i] + " " ;
	if ((new_usr = find_client_nick(data, args[1])) != data.users.end())
	{
		content = ":" + cmd.getSender()->getFull_id() + " NOTICE " +\
		new_usr->getNick_name() + " " + content;
		send_packets(*new_usr, content);
	}
	else
		send_packets(*cmd.getSender(), create_reply(cmd.getSender(), 401) + ERR_NOSUCHNICK(args[1]));
}