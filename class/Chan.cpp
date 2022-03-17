/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chan.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/17 13:02:16 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chan.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Chan::Chan() : _users(),/* _mode(),*/ _topic(), _blacklist_users()
{
}
/**
 * @brief Construct a new Chan:: Chan object
 * 
 * @param usr_operator users create the Chan
 * @param topic_name name of the Chan/topic
 */
Chan::Chan( Users & usr_operator , std::string topic_name,
		std::string mdp_tojoin, bool isprivate = false)
{
	this->_users.push_back(usr_operator);
	this->_topic = topic_name;
	this->_mdp_to_join = mdp_tojoin;
	(void)isprivate;
	// ne pas oublier de passer _mode a private si isprivate == true
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
		// this->_mode = rhs._mode;
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

// /**
//  * @brief send private msg to the user specified
//  * 		but don't open a window
//  * 
//  * @param receiver the user for whom the meaage is intented
//  * @param msg the msg
//  */
// void Chan::msg(Users receiver, std::string msg)
// {
	
// }

// /**
//  * @brief send private msg to the user specified
//  * 		and open a window
//  * 
//  * @param receiver the user who received the msg
//  * @param msg the msg
//  */
// void Chan::query(Users receiver, std::string msg)
// {

// }

// /**
//  * @brief show information about the user specified
//  * 
//  * @param to_stalk the user to stalk
//  */
// void Chan::whois(Users to_stalk)
// {

// }

// /**
//  * @brief users can ignore msg about an other users
//  * 
//  * @param to_ignore the user to ignore
//  * @param want_to_ignore the users who ignore @param to_ignore
//  */
// void Chan::ignore(Users want_to_ignore, Users to_ignore)
// {
	
// }

// /**
//  * @brief users can switch to AFK mode and define a msg to the
//  * 		users who use private msg to them
//  * 
//  * @param msg the defined msg
//  */
// void Chan::away(Users to_away, std::string msg = "I'm currently AFK")
// {
	
// }

// /**
//  * @brief users go back in normal mode (not AFK)
//  * 
//  */
// void Chan::away(Users to_away)
// {}

// /**
//  * @brief user leave the Chan specified
//  * 
//  * @param Chan_name the name of the Chan to leave
//  */
// void Chan::part(std::string Chan_name)
// {}

// void Chan::quit()
// {}

// /**
//  * @brief user can invite an other user
//  * 
//  * @param to_inv the user invited to the Chan
//  * @param Chan_name the name of the Chan
//  */
// void Chan::invite(Users to_inv, std::string Chan_name)
// {}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string		Chan::getTopic(void) const
{
	return this->_topic;
}

/* ************************************************************************** */
