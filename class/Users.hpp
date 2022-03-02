/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/02 17:43:45 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP
# define USERS_HPP

# include <iostream>
# include <string>
# include "../incs/ft_irc.hpp"

class Users
{
	public:
		Users();
		Users( Users const & src );
		~Users();

		Users &		operator=( Users const & rhs );

	private:
		bool	_operator;
		size_t	_id;
		std::string nick_name;
		struct addrinfo	_socket_info;
		std::vector<Users> _ignore_blacklist;

	public:
		std::string getNick_name() const;
		addrinfo	getSocket_info() const;
		void setNick_name(std::string new_nick_name);
		bool is_ignored(Users is_in_blacklist);
};

bool operator==(Users & a, Users & b);
bool operator!=(Users &a, Users &b);

#endif /* *********************************************************** USERS_H */


/*
adresse ip bool v4/v6
nickname std::string
ID = nouvelle id si ip inconnu, sinon garde son ancienne id;
*/