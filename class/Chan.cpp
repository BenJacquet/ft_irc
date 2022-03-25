/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chan.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/25 17:41:34 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chan.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Chan::Chan() : _users(), _mode(), _topic(), _blacklist_users()
{
}
/**
 * @brief Construct a new Chan:: Chan object
 * 
 * @param usr_operator users create the Chan
 * @param topic_name name of the Chan/topic
 */
Chan::Chan( Users & usr_operator , std::string topic_name)
{
	this->addusers(usr_operator);
	this->_topic = topic_name;

}

Chan::Chan( const Chan & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Chan::~Chan()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Chan &				Chan::operator=( Chan const & rhs )
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
 * @brief member function to Change the nickname of the users in the Chan
 * 
 * @param to_Change -> user to Change nickname
 * @param new_nick_name -> the new nickname of the user
 */
void Chan::nick(Users to_Change, std::string new_nick_name)
{
	std::vector<Users>::iterator it = _users.begin();
	while(it != _users.end())
		it++;
	if (it != this->_users.end() && to_Change.getNick_name() != new_nick_name)
	{
		COUT(BLUE, to_Change.getNick_name() << " has a new nick name : " \
			<< new_nick_name << std::endl);
		to_Change.setNick_name(new_nick_name);
	}
}

bool	Chan::addusers(Users to_add)
{
	for(std::vector<Users>::iterator it = this->_users.begin(),
		ite = this->_users.end(); it != ite; it++)
	{
		if (*it == to_add)
			return false;
	}
	this->_users.push_back(to_add);
	return true;
}

bool	Chan::rmusers(Users to_rm)
{
	for(std::vector<Users>::iterator it = this->_users.begin(),
		ite = this->_users.end(); it != ite; it++)
	{
		if (*it == to_rm)
		{
			this->_users.erase(it);
			return true;
		}
	}
	return false;
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string		Chan::getTopic(void) const
{
	return this->_topic;
}

std::vector<Users>	Chan::getUsers(void) const
{
	return (this->_users);
}

/* ************************************************************************** */
