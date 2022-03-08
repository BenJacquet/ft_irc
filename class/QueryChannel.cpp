/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QueryChannel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:55 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/08 16:47:16 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QueryChannel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

QueryChannel::QueryChannel()
{
}

QueryChannel::QueryChannel( const QueryChannel & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

QueryChannel::~QueryChannel()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

QueryChannel &				QueryChannel::operator=( QueryChannel const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, QueryChannel const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

bool	QueryChannel::is_created_Qchannel(Users &a, Users &b)
{
	std::vector<>

}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
