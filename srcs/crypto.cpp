/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:43:24 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/28 17:03:36 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

std::string	encrypt_data(long salt, std::string to_encrypt)
{
	long converted = atoll(to_encrypt.c_str());
	std::ostringstream encrypted;

	encrypted << (converted ^ salt);

	COUT(BLUE, encrypted.str());
	return (encrypted.str());
}