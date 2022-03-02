/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:36:03 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/02 15:30:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_irc.hpp"

/**
 * @brief function that counts how many bytes are stored in str
 * 
 * @param str string to analyze
 * @return amount of bytes stores in str
 */
int ft_strlen(char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return (i);
}