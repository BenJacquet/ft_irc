/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:26:47 by jabenjam          #+#    #+#             */
/*   Updated: 2022/02/28 15:54:02 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
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
#include <poll.h>

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
#define B_BLACK		"\033[1m\033[30m"	/* Bold Black */
#define B_RED		"\033[1m\033[31m"	/* Bold Red */
#define B_GREEN		"\033[1m\033[32m"	/* Bold Green */
#define B_YELLOW	"\033[1m\033[33m"	/* Bold Yellow */
#define B_BLUE		"\033[1m\033[34m"	/* Bold Blue */
#define B_MAGENTA	"\033[1m\033[35m"	/* Bold Magenta */
#define B_CYAN		"\033[1m\033[36m"	/* Bold Cyan */
#define B_WHITE		"\033[1m\033[37m"	/* Bold White */
#define L_RED		"\033[91m"			/* Light Red */
#define L_GREEN		"\033[92m"			/* Light Green */
#define L_YELLOW	"\033[93m"			/* Light Yellow */
#define L_BLUE		"\033[94m"			/* Light Blue */
#define L_MAGENTA	"\033[95m"			/* Light Magenta */
#define L_CYAN		"\033[96m"			/* Light Cyan */

// TYPEDEFS

typedef std::map<int, struct sockaddr_in> client_map;
typedef std::pair<int, struct sockaddr_in> client_pair;
typedef std::vector<struct pollfd> pollfds;


// STRUCTS

typedef struct			s_data
{
	uint16_t			port;			// port d'ecoute (SERVEUR)
	int					sock_fd;		// fd du socket d'entree (SERVEUR)
	struct addrinfo		*bind_addr;		// socket (SERVEUR)
	pollfds				poll_fds;		// vector de pollfds clients (CLIENTS)
	client_map			client_socks;	// map contenant les fd et sockets (CLIENTS)
	int					timeout;		// ms avant de timeout
}						t_data;

// TEMPLATES

// HEADER

#define ASCII_HEADER "\
'########:'########:::::::::'####:'########:::'######:::::'##:::::::::'#######::\n\
 ##.....::... ##..::::::::::. ##:: ##.... ##:'##... ##:::: ##:::'##::'##.... ##:\n\
 ##:::::::::: ##::::::::::::: ##:: ##:::: ##: ##:::..::::: ##::: ##::..::::: ##:\n\
 ######:::::: ##::::::::::::: ##:: ########:: ##:::::::::: ##::: ##:::'#######::\n\
 ##...::::::: ##::::::::::::: ##:: ##.. ##::: ##:::::::::: #########:'##::::::::\n\
 ##:::::::::: ##::::::::::::: ##:: ##::. ##:: ##::: ##::::...... ##:: ##::::::::\n\
 ##:::::::::: ##::'#######::'####: ##:::. ##:. ######::::::::::: ##:: #########:\n\
..:::::::::::..::::.......::....::..:::::..:::......::::::::::::..:::.........::\n\
\n\nIRC SERVER FOR 42 CURSUS CODED BY : JABENJAM THOBERTH\n"