/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/02 15:50:55 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Users.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Users::Users() : _operator(false), _socket_info()
{
}

Users::Users( const Users & src )
{
	*this = src; /* rappel : revient a utiliser l'operator= */
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Users::~Users()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Users &				Users::operator=( Users const & rhs )
{
	if ( this != &rhs )
	{
		this->_operator = rhs._operator;
		this->_socket_info = rhs._socket_info;
	}
	return *this;
}

/**
 * @brief comparaison between 2 Users
 * 
 * @param a user a
 * @param b user b
 * @return true if equal
 * @return false if not_equal
 */
bool operator==(Users &a, Users &b)
{
	if (a.getSocket_info().ai_family != b.getSocket_info().ai_family)
		return false;
	if (a.getSocket_info().ai_addr->sa_data != b.getSocket_info().ai_addr->sa_data)
		return false;
	return true;
}

bool operator!=(Users &a, Users &b)
{
	return (!(a == b));
}

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string	Users::getNick_name() const
{
	return this->nick_name;
}

addrinfo	Users::getSocket_info() const
{
	return this->_socket_info;
}

void Users::setNick_name(std::string new_nick_name)
{
	this->nick_name = new_nick_name;
}

bool Users::is_ignored(Users is_in_blacklist)
{
	if (this->_ignore_blacklist.size() == 0)
		return false;
	std::vector<Users>::iterator it = this->_ignore_blacklist.begin();
	for (; it != this->_ignore_blacklist.end(); it++)
	{
		if (*it == is_in_blacklist)
			return true;
	}
	return false;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
