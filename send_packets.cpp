/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packets.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:41:23 by thoberth          #+#    #+#             */
/*   Updated: 2022/02/28 16:51:09 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_irc.hpp"

size_t ft_strlen(char * to_send)
{
	int i = 0;
	if (!to_send)
		return (0);
	while (to_send[i])
		i++;
	return (i);
}

/*
**	fonction qui pour utiliser send(), de maniere safe
**	renvoie la taille envoye ou -1 si send() echoue
*/
size_t send_packets(int client_fd, char *to_send)
{
	size_t len = ft_strlen(to_send);
	size_t ret = 0;
	while (ret != len || ret != -1)
	{
		ret += send(client_fd, to_send + ret, (sizeof(char*) * len) - ret, 0);
	}
	if (ret == -1)
		CERR(YELLOW, "Couldn't send packet!");
	return ret;
}
