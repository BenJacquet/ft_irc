/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QueryChannel.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:55 by thoberth          #+#    #+#             */
/*   Updated: 2022/03/08 16:45:16 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUERYCHANNEL_HPP
# define QUERYCHANNEL_HPP

# include <iostream>
# include <string>
# include "../incs/ft_irc.hpp"
# include "Users.hpp"

class QueryChannel
{

	public:

		QueryChannel();
		QueryChannel(Users a, Users b);
		QueryChannel( QueryChannel const & src );
		~QueryChannel();

		QueryChannel &		operator=( QueryChannel const & rhs );

	private:
		std::vector<std::pair<Users, Users> > _vector_Qchannel;

	public:
		bool	is_created_Qchannel(Users &a, Users &b);
};


#endif /* **************************************************** QUERYCHANNEL_H */
