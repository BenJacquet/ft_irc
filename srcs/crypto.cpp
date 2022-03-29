/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:43:24 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/29 21:01:36 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

std::string	encrypt_data(long salt, std::string to_encrypt)
{
	unsigned long converted = 0;
	std::string::iterator it = to_encrypt.begin();
	std::string::iterator end = to_encrypt.end();

	for (; it != end; it++)
	{
		COUT(YELLOW, "char=" << (*it) << "\ncasted=" << static_cast<unsigned long>(*it));
		converted += pow(static_cast<unsigned long>(*it), 2);
	}
	converted = pow(converted, 2);
	std::ostringstream encrypted;

	encrypted << std::hex << (converted ^ salt);

	COUT(BLUE, "Clear data=" << to_encrypt << "\nLong data=" << converted << "\nEncrypted data=" << encrypted.str());
	return (encrypted.str());
}