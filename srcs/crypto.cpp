/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:43:24 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/04 11:42:52 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief Very basic encryption algorithm that hashes a string,
 * applies a salt generated at runtime and converts it into a hexadecimal string
 * 
 * @param salt 
 * @param to_encrypt 
 * @return std::string 
 */
std::string	encrypt_data(long salt, std::string to_encrypt)
{
	unsigned long long converted = 0;
	std::string::iterator it = to_encrypt.begin();
	std::string::iterator end = to_encrypt.end();

	for (; it != end; it++)
	{
		converted += static_cast<double>(pow(static_cast<double>(*it), 2));
	}
	converted = static_cast<double>(pow(static_cast<double>(converted), 2));
	std::ostringstream encrypted;

	encrypted << std::hex << (converted ^ salt);
	return (encrypted.str());
}