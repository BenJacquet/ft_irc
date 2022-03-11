/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:22:10 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/11 16:04:19 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(Users* sender, std::string payload)
:_sender(sender)
,_destination(sender) /* a initialiser apres parsing */
,_payload(payload)
{
	//std::cout << "Default constructor for Message called" << std::endl
}

Message::Message(const Message &src)
:_sender(src.getSender())
,_destination(src.getDestination())
,_payload(src.getPayload())
{
	//std::cout << "Copy constructor for Message called" << std::endl
}

Message::~Message() {/*std::cout << "Destructor for Message called" << std::endl*/}

Message & Message::operator=(const Message &src)
{
	//std::cout << "Copy assignment for Message called" << std::endl
	if (this == &src)
		return (*this);
	return (*this);
}

Users* Message::getSender() const
{
	return (this->_sender);
}

Users* Message::getDestination() const
{
	return (this->_destination);
}

std::string Message::getPayload() const
{
	return (this->_payload);
}
