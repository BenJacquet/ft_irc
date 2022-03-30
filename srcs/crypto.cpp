/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:43:24 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/30 07:46:38 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

std::string	encrypt_data(long salt, std::string to_encrypt)
{
	unsigned long long converted = 0;
	std::string::iterator it = to_encrypt.begin();
	std::string::iterator end = to_encrypt.end();

	for (; it != end; it++)
	{
		// COUT(YELLOW, "char=" << (*it) << "\ncasted=" << static_cast<unsigned long>(*it));
		converted += static_cast<double>(pow(static_cast<double>(*it), 2));
	}
	converted = static_cast<double>(pow(static_cast<double>(converted), 2));
	std::ostringstream encrypted;

	encrypted << std::hex << (converted ^ salt);

	// COUT(BLUE, "Clear data=" << to_encrypt << "\nLong data=" << converted << "\nEncrypted data=" << encrypted.str());
	return (encrypted.str());
}