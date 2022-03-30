/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:09:34 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/29 23:15:32 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"


void	who_command_parsing(t_data &data, Message &cmd)
{
	std::vector<std::string> args = parse_line(cmd.getPayload());
	if (args[0].compare(0, 5, "WHOIS") == 0)
		whois_parsing(data, cmd);
	else if (args[0].compare(0, 6, "WHOWAS") == 0)
		whowas_parsing(data, cmd);
	else
		who_parsing(data, cmd);
}
/**
 * @brief 
 *	6 < WHO #t
 		<full_id sender>            RPL	nickname	<channel>	<user>		<host><server>	<nick if user not mode +i>	( ”H“ / ”G“ > [”*“] [ ( ”@“ / ”+“ ) ] :<hopcount> <real name>
	6 > :toto2__!thoberth@localhost 352	toto2__		#t 			thoberth	localhost 		toto2_ H :0 42boss
	6 > :toto2__!thoberth@localhost 352 toto2__ #t thoberth localhost  toto2__ H :0 42boss
	6 > :toto2__!thoberth@localhost 352 toto2__ #t thoberth localhost  toto2___ H :0 42boss
	6 > :toto2__!thoberth@localhost 315 toto2__ thoberth :End of /WHO list
 * @param data 
 * @param cmd 
 */
void	who_parsing(t_data &data, Message &cmd)
{
	(void)data;
	std::vector<std::string> args = parse_line(cmd.getPayload());
	CERR(GREEN, cmd.getSender()->getFd() << " > who");
	for (std::vector<std::string>::iterator it = args.begin(), ite = args.end();
		it != ite; it++)
		CERR(GREEN, "args = |" << *it << '|');
	
}

/**
 * if whois dont found the nickname -> irssi send Whowas query
 */
void	whois_parsing(t_data &data, Message &cmd)
{
	(void)data;
	CERR(GREEN, cmd.getSender()->getFd() << " > whois");
	std::vector<std::string> args = parse_line(cmd.getPayload());
	for (std::vector<std::string>::iterator it = args.begin(), ite = args.end();
		it != ite; it++)
		CERR(GREEN, "args = |" << *it << '|');
}

void	whowas_parsing(t_data &data, Message &cmd)
{
	(void)data;
	CERR(GREEN, cmd.getSender()->getFd() << " > whowas");
	std::vector<std::string> args = parse_line(cmd.getPayload());
	for (std::vector<std::string>::iterator it = args.begin(), ite = args.end();
		it != ite; it++)
		CERR(GREEN, "args = |" << *it << '|');
}
