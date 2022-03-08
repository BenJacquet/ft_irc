/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/08 13:32:42 by thoberth         ###   ########.fr       */
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

/**
 * @brief member function to change the nickname of the users in the channel
 * 
 * @param to_change -> user to change nickname
 * @param new_nick_name -> the new nickname of the user
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

/**
 * @brief send private msg to the user specified
 * 		but don't open a window
 * 
 * @param receiver the user for whom the meaage is intented
 * @param msg the msg
 */
void Channel::msg(Users receiver, std::string msg)
{
	
}

/**
 * @brief send private msg to the user specified
 * 		and open a window
 * 
 * @param receiver the user who received the msg
 * @param msg the msg
 */
void Channel::query(Users receiver, std::string msg = std::string())
{

}

/**
 * @brief show information about the user specified
 * 
 * @param to_stalk the user to stalk
 */
void Channel::whois(Users to_stalk)
{

}

/**
 * @brief users can ignore msg about an other users
 * 
 * @param to_ignore the user to ignore
 * @param want_to_ignore the users who ignore @param to_ignore
 */
void Channel::ignore(Users want_to_ignore, Users to_ignore)
{
	
}

/**
 * @brief users can switch to AFK mode and define a msg to the
 * 		users who use private msg to them
 * 
 * @param msg the defined msg
 */
void Channel::away(Users to_away, std::string msg = "I'm currently AFK")
{
	
}

/**
 * @brief users go back in normal mode (not AFK)
 * 
 */
void Channel::away(Users to_away)
{}

/**
 * @brief user leave the channel specified
 * 
 * @param chan_name the name of the channel to leave
 */
void Channel::part(std::string chan_name)
{}

void Channel::quit()
{}

/**
 * @brief user can invite an other user
 * 
 * @param to_inv the user invited to the channel
 * @param chan_name the name of the channel
 */
void Channel::invite(Users to_inv, std::string chan_name)
{}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
