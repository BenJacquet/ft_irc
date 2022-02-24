/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_tests.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:47:12 by jabenjam          #+#    #+#             */
/*   Updated: 2022/02/24 17:23:26 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <list>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

#include "string.h"

// DEFINES

#define BUFFERSIZE 4096

#define COUT(COLOR, DATA) std::cout << COLOR << DATA << RESET << std::endl
#define CERR(COLOR, DATA) std::cout << COLOR << DATA << RESET << std::endl

#define RESET		"\033[0m"			/* Reset*/
#define BLACK		"\033[30m"			/* Black */
#define RED			"\033[31m"			/* Red */
#define GREEN		"\033[32m"			/* Green */
#define YELLOW		"\033[33m"			/* Yellow */
#define BLUE		"\033[34m"			/* Blue */
#define MAGENTA		"\033[35m"			/* Magenta */
#define CYAN		"\033[36m"			/* Cyan */
#define WHITE		"\033[37m"			/* White */
#define BOLDBLACK	"\033[1m\033[30m"	/* Bold Black */
#define BOLDRED		"\033[1m\033[31m"	/* Bold Red */
#define BOLDGREEN	"\033[1m\033[32m"	/* Bold Green */
#define BOLDYELLOW	"\033[1m\033[33m"	/* Bold Yellow */
#define BOLDBLUE	"\033[1m\033[34m"	/* Bold Blue */
#define BOLDMAGENTA	"\033[1m\033[35m"	/* Bold Magenta */
#define BOLDCYAN	"\033[1m\033[36m"	/* Bold Cyan */
#define BOLDWHITE	"\033[1m\033[37m"	/* Bold White */

// TYPEDEFS

typedef std::map<int, struct sockaddr_in> client_map;
typedef std::pair<int, struct sockaddr_in> client_pair;

// STRUCTS

typedef struct			s_data
{
	uint16_t			port;
	int					sock_fd;
	client_map			client_socks;
	sockaddr_in			server_sock;
}						t_data;

// TEMPLATES