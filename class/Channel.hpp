/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:30 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/01 15:19:47 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "../incs/ft_irc.hpp"
# include "Users.hpp"


class Channel
{
	public:
		Channel();
		Channel( Channel const & src );
		~Channel();

		Channel &		operator=( Channel const & rhs );

	private:
		std::vector<Users> _users;
		std::string _mode;
		std::string _topic; /* name ? */
		std::vector<Users> _blacklist_users;

	public:
		void nick(Users to_change, std::string new_nick_name);
		void msg(Users receiver, std::string msg);
		void query(Users receiver, std::string msg = std::string());
		void whois(Users to_stalk);
		void ignore(Users to_ignore);
		void away(std::string msg );
		void away();
		void part(std::string chan_name);
		void quit();
		void invite(Users to_inv, std::string chan_name);
};

#endif /* ********************************************************* CHANNEL_H */
