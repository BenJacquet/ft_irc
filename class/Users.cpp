/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/11 13:28:46 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Users.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Users::Users()
{
}

Users::Users(int fd, sockaddr sock_addr)
{
	this->_fd = fd;
	this->_socket_addr = sock_addr;
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
		this->_socket_addr = rhs._socket_addr;
	}
	return *this;
}

/**
 *  @brief comparaison between 2 Users
 * 
 * @param a user a
 * @param b user b
 * @return true if equal
 * @return false if not_equal
 */
bool operator==(Users &a, Users &b)
{
	if (a.getUid() != b.getUid())
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

// void			Users::msg(Users to_send, std::string content)
// {
	
// }

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/*
** 					GETTERS					**
*/

int			Users::getUid() const
{
	return this->_uid;
}

int				Users::getFd() const
{
	return this->_fd;
}

int				Users::getOperator() const
{
	return this->_operator;
}

std::string		Users::getReal_name() const
{}

std::string	Users::getNick_name() const
{
	return this->_nick_name;
}

std::string		Users::getPw() const
{
	return this->_pw;
}

int				Users::getReg_status() const
{
	return this->_reg_status;
}

sockaddr	Users::getSocket_addr() const
{
	return this->_socket_addr;
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
** 					SETTERS					**
*/

void			Users::setReal_name(std::string new_real_name)
{
	this->_real_name = new_real_name;
}

void			Users::setNick_name(std::string new_nick_name)
{
	this->_nick_name = new_nick_name;
}

void			Users::setPw(std::string new_pw)
{
	this->_pw = new_pw;
}

void			Users::setReg_status(int new_status)
{
	this->_reg_status = new_status;
}

void			Users::add_blacklist(Users to_add)
{
	if (this->_ignore_blacklist.size() > 0)
	{
		std::vector<Users>::iterator it = this->_ignore_blacklist.begin();
		for(; it != this->_ignore_blacklist.end(); it++)
		{
			if (*it == to_add)
			{
				CERR(RED, to_add.getReal_name() << "is already in the black list");
				return ;
			}
		}
	}
	this->_ignore_blacklist.push_back(to_add);
}


/* ************************************************************************** */
