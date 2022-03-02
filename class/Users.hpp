/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/01 17:30:32 by thoberth         ###   ########.fr       */
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
		std::string nick_name;
		struct addrinfo	_socket_info;

	public:
		std::string getNick_name() const;
		void setNick_name(std::string new_nick_name);
};

#endif /* *********************************************************** USERS_H */
