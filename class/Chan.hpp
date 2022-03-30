/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chan.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/30 06:03:58 by thoberth         ###   ########.fr       */
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
		std::string _mode;
		std::string	_mdp_to_join;
		std::string _topic; /* name ? */
		std::vector<Users> _blacklist_users;

	public:
	/*		METHOD		*/
	/*		GETTERS		*/
		std::string			getMode(void) const;
		std::string			getTopic(void) const;
		std::vector<Users>	getUsers(void) const;
	/*		SETTERS		*/
		void setMode(std::string neW_mode);
		bool addusers(Users to_add);
		bool rmusers(Users to_rm);
};

#endif /* ********************************************************* Chan_H */
