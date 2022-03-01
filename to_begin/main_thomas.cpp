/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thomas.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:53:55 by thoberth          #+#    #+#             */
/*   Updated: 2022/02/28 14:33:20 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_irc.hpp"
#include <sys/types.h>
#include <sys/socket.h>

/*
** int socket(int domain, int type, int protocol)
** domain = PF_INET , type = SOCK_STREAM or SOCK_DGRAM, protocol = 0 (defined automatically with the type)
** return a fd for the new socket or -1 if failed
*/

/*
** int bind(int sockfd, const struct sockadrr * addr, socklen_t addrlen)
** 
*/


/*
** int connect(int sockfd, const struct sockaddr * addr, socklen_t addrlen)
** The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr
** The addrlen argument specifies the size of addrq
**
*/

/*
** When socket are connected :
**
** ssize_t send(int sockfd, const void *buf, size_t len, int flags)
** used to transmit a msg to another socket.
** return the number of bytes sent or -1 if failed
**
** ssize_t recv(int sockfd, void *buf, size_t len, int flags)
** receive a msg from a socket
** return the number of bytes received or -1 if failed
**
*/

int main()
{
	
}