/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:28:59 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/20 15:16:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP
# define USERS_HPP

# include <iostream>
# include <string>
# include "../incs/ft_irc.hpp"

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
		Users();
		Users( int fd, sockaddr_in6 sock_addr, struct s_data &data );
		Users( Users const & src );
		~Users();

		Users &		operator=( Users const & rhs );

	private:
		unsigned int		_uid; /* G & S */
		int					_fd; /* G & S */
		bool				_online; /* G & S */
		std::string			_mode; /* G & S */
		std::string			_host_name; /* G & S */
		std::string			_user_name; /* G & S */
		std::string			_full_id; /* G & S */ /* nickname!user_name@hostname */
		std::string			_real_name; /* G & S */
		std::string			_nick_name; /* G & S */
		std::string			_pw; /* G & S */
		std::string			_away_mode; /* G & S */
		int					_reg_status; /* G & S */
		bool				_in_use; /* G & S */
		int					_authenticated; /* G & S */
		struct sockaddr_in6	_socket_addr; /* G & S */
		std::string			_ip; /* G & S */

	public:
		/*		METHODS		*/
		void			disconnect();
		void			connect(Users &to_replace);
		/*		GETTERS		*/
		unsigned int	getUid() const;
		int				getFd() const;
		bool			getOnline() const;
		std::string		getMode() const;
		std::string		getHost_name() const;
		std::string		getUser_name() const;
		std::string		getFull_id() const;
		std::string		getReal_name() const;
		std::string		getNick_name() const;
		std::string		getPw() const;
		std::string		getAway_mode() const;
		int				getReg_status() const;
		bool			getIn_use() const;
		int				getAuthenticated() const;
		sockaddr_in6	getSocket_addr() const;
		std::string		getIp() const;
		/*		SETTERS		*/
		void			setUid(unsigned int new_uid);
		void			setFd(int fd);
		void			setOnline(bool online);
		void			setMode(std::string new_mode);
		void			setHostname(std::string new_host_name);
		void			setUser_name(std::string new_user_name);
		void			setFull_id(std::string new_full_id);
		void			setReal_name(std::string new_real_name);
		void			setNick_name(std::string new_nick_name);
		void			setPw(std::string new_pw);
		void			setAway_mode(std::string new_away_mode);
		void			setReg_status(int new_status);
		void			setIn_use(bool in_use);
		void			setAuthenticated(int authenticated);
		void			setSocket_addr(sockaddr_in6 new_sock_add);
		void			setIp(std::string ip);
};

bool operator==(Users & a, Users & b);
bool operator!=(Users & a, Users & b);
std::ostream &operator<<(std::ostream &COUT, Users &user);

#endif /* *********************************************************** USERS_H */
