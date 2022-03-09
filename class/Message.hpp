/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:21:31 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/09 16:38:46 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../incs/ft_irc.hpp"

class Message
{
	private:
		int			_sender;
		int			_destination;
		std::string	_payload;
	public:
		//CANONICAL FORM COMPONENTS
		Message(int sender, std::string payload);
		Message(const Message & src);
		~Message();
		Message & operator=(const Message & src);
		//OTHER COMPONENTS
		int getSender() const;
		int getDestination() const;
		std::string getPayload() const;
};
