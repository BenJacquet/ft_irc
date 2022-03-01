/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/01 17:31:18 by thoberth         ###   ########.fr       */
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

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string	Users::getNick_name() const
{
	return this->nick_name;
}

void Users::setNick_name(std::string new_nick_name)
{
	this->nick_name = new_nick_name;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
