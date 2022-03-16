/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/16 17:29:32 by thoberth         ###   ########.fr       */
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
		Chan( Users & usr_operator, std::string topic_name,
			std::string mdp_tojoin, bool isprivate);
		Chan( Chan const & src );
		~Chan();

		Chan &		operator=( Chan const & rhs );

	private:
		std::vector<Users> _users;
		// std::string _mode;
		std::string	_mdp_to_join;
		std::string _topic; /* name ? */
		std::vector<Users> _blacklist_users;

	public:
	/*		METHOD		*/
		void nick(Users to_Change, std::string new_nick_name);
		// void msg(Users receiver, std::string msg);
		// void query(Users receiver, std::string msg = std::string());
		// void whois(Users to_stalk);
		// void ignore(Users want_to_ignore, Users to_ignore);
		// void away(Users to_away, std::string msg);
		// void away(Users to_not_away);
		// void part(std::string Chan_name);
		// void quit();
		// void invite(Users to_inv, std::string Chan_name);
	/*		GETTERS		*/
	/*		SETTERS		*/
		bool addusers(Users to_add);
};

#endif /* ********************************************************* Chan_H */
