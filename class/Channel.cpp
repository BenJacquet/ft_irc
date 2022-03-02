/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/01 17:31:37 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel() : _users(), _mode(), _topic(), _blacklist_users()
{
}

Channel::Channel( const Channel & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel &				Channel::operator=( Channel const & rhs )
{
	if ( this != &rhs )
	{
		this->_users = rhs._users;
		this->_mode = rhs._mode;
		this->_topic = rhs._topic;
		this->_blacklist_users = rhs._blacklist_users;
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void Channel::nick(Users to_change, std::string new_nick_name)
{
	std::vector<Users>::iterator it = _users.begin();
	while(it != _users.end())
		it++;
	if (it != this->_users.end() && to_change.getNick_name() != new_nick_name)
	{
		COUT(BLUE, to_change.getNick_name() << " has a new nick name : " \
			<< new_nick_name << std::endl);
		to_change.setNick_name(new_nick_name);
	}
}

void Channel::msg(Users receiver, std::string msg)
{
	
}

void Channel::query(Users receiver, std::string msg = std::string())
{}

void Channel::whois(Users to_stalk)
{}

void Channel::ignore(Users to_ignore)
{}

void Channel::away(std::string msg)
{}

void Channel::away()
{}

void Channel::part(std::string chan_name)
{}

void Channel::quit()
{}

void Channel::invite(Users to_inv, std::string chan_name)
{}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
