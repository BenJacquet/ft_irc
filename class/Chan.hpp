/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chan.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/05/02 11:36:15 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Chan_HPP
# define Chan_HPP

# include <iostream>
# include <string>
# include "../incs/ft_irc.hpp"

class Users;

class Chan
{
	public:
		Chan();
		Chan( Users & usr_operator, std::string topic_name);
		Chan( Chan const & src );
		~Chan();

		Chan &		operator=( Chan const & rhs );

	private:
		std::vector<Users> _users;
		Users	*_creator;
		std::string _mode;
		std::string _limit_user;
		std::string	_mdp_to_join;
		std::string _name; /* name ? */
		std::vector<Users> _blacklist_users;

	public:
	/*		METHOD		*/
		bool addusers(Users to_add);
		bool rmusers(Users to_rm);
		bool add_toBlacklist(Users to_add);
		bool rm_toBlacklist(Users to_rm);
		bool is_banned(Users &is_ban);
	/*		GETTERS		*/
		Users			&	getCreator(void) const;
		std::string			getMode(void) const;
		std::string			getLimit_user(void) const;
		std::string			getPw(void) const;
		std::string			getName(void) const;
		std::vector<Users>	getUsers(void) const;
		std::vector<Users>	getBlacklist(void) const;
	/*		SETTERS		*/
		void setMode(std::string new_mode);
		void setLimit_user(std::string nbr);
		void setPw(std::string new_pw);
};

#endif /* ********************************************************* Chan_H */
