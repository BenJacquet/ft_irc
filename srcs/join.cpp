/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:14:21 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/16 17:41:05 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

int		join_parsing(t_data &data, Message &cmd)
{
	
}

/**
 * @brief /join if name_Chan don't exist (here) creator create name_Chan
 * 
 * @param data struct who store everything
 * @param creator creator of the Chan
 * @param name_Chan name of the Chan
 * @param mdp_tojoin the password if isprivate is true
 * @param isprivate false if no passw to set else true
 * @return 1 if Chan is created, 0 if something went wrong
 */
int		join(t_data &data, Users creator, std::string name_Chan,
	std::string mdp_tojoin = "none", bool isprivate = false)
{
	t_data.chans.push_back(Chan(creator, name_Chan, mdp_tojoin, isprivate));
	return (1);
}
