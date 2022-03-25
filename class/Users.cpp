/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/25 15:24:27 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Users.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Users::Users()
{
}

Users::Users(int fd, sockaddr_in6 sock_addr, struct s_data &data)
{
	srand(time(NULL));

	this->_fd = fd;
	this->_socket_addr = sock_addr;
	this->_reg_status = 0;
	this->_online = 0;
	unsigned int uid = static_cast<unsigned int>(random() % __INT_MAX__);
	for (; find_client_uid(data, uid) != data.users.end();)
		uid = static_cast<unsigned int>(random() % __INT_MAX__);
	this->_uid = uid;
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
		this->_uid = rhs._uid;
		this->_fd = rhs._fd;
		this->_operator = rhs._operator;
		this->_online = rhs._online;
		this->_host_name = rhs._host_name;
		this->_user_name = rhs._user_name;
		this->_full_id = rhs._full_id;
		this->_real_name = rhs._real_name;
		this->_nick_name = rhs._nick_name;
		this->_pw = rhs._pw;
		this->_reg_status = rhs._reg_status;
		this->_socket_addr = rhs._socket_addr;
		this->_ignore_blacklist = rhs._ignore_blacklist;
		
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

void			Users::disconnect()
{
	this->setOnline(false);
	this->setFd(-1);
}

void			Users::connect(Users *user)
{
	this->setOnline(true);
	this->setFd(user->getFd());
	this->setFull_id(user->getFull_id());
	this->setHost_name(user->getHost_name());
	this->setReal_name(user->getReal_name());
	this->setSocket_addr(user->getSocket_addr());
	this->setUser_name(user->getUser_name());
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/*
** 					GETTERS					**
*/

unsigned int	Users::getUid() const
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

std::string		Users::getHost_name() const
{
	return this->_host_name;
}

std::string		Users::getUser_name() const
{
	return this->_user_name;
}

std::string		Users::getFull_id() const
{
	return this->_full_id;
}

std::string		Users::getReal_name() const
{
	return this->_real_name;
}

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

bool			Users::getIn_use() const
{
	return this->_in_use;
}


sockaddr_in6	Users::getSocket_addr() const
{
	return this->_socket_addr;
}

bool			Users::getOnline() const
{
	return this->_online;
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

void			Users::setUid(unsigned int new_uid)
{
	this->_uid = new_uid;
}

void			Users::setFd(int fd)
{
	this->_fd = fd;
}

void			Users::setOperator(bool op)
{
	this->_operator = op;
}

void			Users::setOnline(bool online)
{
	this->_online = online;
}

void			Users::setHost_name(std::string new_host_name)
{
	this->_host_name = new_host_name;
}

void			Users::setUser_name(std::string new_user_name)
{
	this->_user_name = new_user_name;
}

void			Users::setFull_id(std::string new_full_id)
{
	this->_full_id = new_full_id;
}

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

void			Users::setIn_use(bool in_use)
{
	this->_in_use = in_use;
}

void			Users::setSocket_addr(sockaddr_in6 new_sock_add)
{
	this->_socket_addr = new_sock_add;
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
