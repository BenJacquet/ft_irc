/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/11 13:28:34 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP
# define USERS_HPP

# include <iostream>
# include <string>
# include "../incs/ft_irc.hpp"
/*
0000 0111
2^2 PASS_W
2^1 NICK_N
2^0 REAL_N
*/

/**
 * @brief class Users
 * 
 * int _uid
 * int		fd;
 * std::string real_name
 * "          " nick_name
 * "          " _pw
 * int			registration_status -> / look above /
 * sockaddr		_socket_info
 * vector<Users> blacklist
 * int			_operator -> / 0 = regular user || 1 = local operator || 2 = global operator /
 */
class Users
{
	public:
		Users( int fd, sockaddr sock_addr);
		Users( Users const & src );
		~Users();

		Users &		operator=( Users const & rhs );

	private:
		Users(); /* do not use this constructor */
		int					_uid;
		int					_fd;
		int					_operator;
		std::string			_real_name;
		std::string			_nick_name;
		std::string			_pw;
		int					_reg_status;
		struct sockaddr		_socket_addr;
		std::vector<Users>	_ignore_blacklist;

	public:
		/*		METHODS		*/
		//void			msg(Users to_send, std::string content);
		/*		GETTERS		*/
		int				getUid() const;
		int				getFd() const;
		int				getOperator() const;
		std::string		getReal_name() const;
		std::string		getNick_name() const;
		std::string		getPw() const;
		int				getReg_status() const;
		sockaddr		getSocket_addr() const;
		bool			is_ignored(Users is_in_blacklist);
		/*		SETTERS		*/
		void			setReal_name(std::string new_real_name);
		void			setNick_name(std::string new_nick_name);
		void			setPw(std::string new_pw);
		void			setReg_status(int new_status);
		void			add_blacklist(Users to_add);
};

bool operator==(Users & a, Users & b);
bool operator!=(Users &a, Users &b);

#endif /* *********************************************************** USERS_H */
