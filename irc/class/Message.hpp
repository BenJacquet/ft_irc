/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:21:31 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/20 15:02:00 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../incs/ft_irc.hpp"

class Users;

class Message
{
	private:
		Users				*_sender;
		Users				*_destination;
		std::string		_payload;
	public:
		//CANONICAL FORM COMPONENTS
		Message(Users *sender, std::string payload);
		Message(const Message & src);
		~Message();
		Message & operator=(const Message & src);
		//OTHER COMPONENTS
		Users *getSender() const;
		Users *getDestination() const;
		std::string getPayload() const;
		void setSender(Users *sender);
};
