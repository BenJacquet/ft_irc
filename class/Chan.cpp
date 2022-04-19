/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chan.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/04/19 16:37:41 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chan.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Chan::Chan() : _users(), _creator(), _mode(), _name(), _blacklist_users()
{
}
/**
 * @brief Construct a new Chan:: Chan object
 * 
 * @param usr_operator users create the Chan
 * @param topic_name name of the Chan/topic
 */
Chan::Chan( Users & usr_operator , std::string name) : _creator(&usr_operator)
{
	this->addusers(usr_operator);
	this->_name = name;
	this->_mode = "+l";
	this->_limit_user = "25";

}

Chan::Chan( const Chan & src ) : _creator(src._creator)
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
		this->_limit_user = rhs._limit_user;
		this->_mdp_to_join= rhs._mdp_to_join;
		this->_name = rhs._name;
		this->_blacklist_users = rhs._blacklist_users;
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

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

bool	Chan::add_toBlacklist(Users to_add)
{
	for(std::vector<Users>::iterator it = this->_blacklist_users.begin(),
		ite = this->_blacklist_users.end(); it != ite; it++)
	{
		if (*it == to_add)
			return false;
	}
	this->_blacklist_users.push_back(to_add);
	return true;
}

bool	Chan::rm_toBlacklist(Users to_rm)
{
	for(std::vector<Users>::iterator it = this->_blacklist_users.begin(),
		ite = this->_blacklist_users.end(); it != ite; it++)
	{
		if (*it == to_rm)
		{
			this->_blacklist_users.erase(it);
			return true;
		}
	}
	return false;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

Users	&		Chan::getCreator(void) const
{
	return *this->_creator;
}

std::string		Chan::getMode(void) const
{
	return this->_mode;
}

std::string		Chan::getLimit_user(void) const
{
	return this->_limit_user;
}

std::string		Chan::getPw(void) const
{
	return this->_mdp_to_join;
}

std::string		Chan::getName(void) const
{
	return this->_name;
}

std::vector<Users>	Chan::getUsers(void) const
{
	return (this->_users);
}

std::vector<Users>	Chan::getBlacklist(void) const
{
	return (this->_blacklist_users);
}

void	Chan::setMode(std::string new_mode)
{
	this->_mode = new_mode;
}

void	Chan::setLimit_user(std::string nbr)
{
	this->_limit_user = nbr;
}

void	Chan::setPw(std::string new_pw)
{
	this->_mdp_to_join = new_pw;
}

/* ************************************************************************** */
