/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:26:47 by jabenjam          #+#    #+#             */
/*   Updated: 2022/03/15 17:00:48 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <sstream>
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
#include <unistd.h>
#include <signal.h>

#include <string.h>

// #include "../class/Channel.hpp"
#include "../class/Users.hpp"
#include "../class/Message.hpp"

class Message;
class Users;

// DEFINES

#define BUFFERSIZE 4096

#define BACKLOG 10

#define COUT(COLOR, DATA) (std::cout << COLOR << DATA << RESET << std::endl)
#define CERR(COLOR, DATA) (std::cerr << COLOR << DATA << RESET << '\n')

// TYPEDEFS

typedef std::vector<struct pollfd>			v_pollfds;
typedef std::vector<Users> 					v_Users;
typedef struct std::pair<std::string, void (*)(struct s_data&, Message&)>	p_Command;
typedef std::map<std::string, void (*)(struct s_data&, Message&)>	m_Commands;

// STRUCTS

typedef struct			s_data
{
	uint16_t			port;			// port d'ecoute (SERVEUR)
	int					sock_fd;		// fd du socket d'entree (SERVEUR)
	struct addrinfo		*bind_addr;		// socket (SERVEUR)
	v_pollfds			poll_fds;		// vector de pollfds clients (CLIENTS)
	v_Users				users;			// vector des utilisateurs connectés
	m_Commands			commands;		// map qui contient en key->string de la commande et value->fonction pointeur
	int					timeout;		// ms avant de timeout
}						t_data;

// PROTOTYPES

	/* FD MANAGEMENT */

		v_pollfds::iterator find_fd(t_data &data, int fd); //AUTHOR: jabenjam
		void remove_fd(t_data &data, int fd); //AUTHOR: jabenjam
		void add_fd(t_data &data, int fd); //AUTHOR: jabenjam
		int new_connection(t_data &data); //AUTHOR: jabenjam

	/* IO OPERATIONS */

		int io_loop(t_data &data, Users &client); //AUTHOR: jabenjam
		int receive_packets(t_data &data, Users &client); //AUTHOR: jabenjam
		int send_packets(int client, std::string to_send); //AUTHOR: thoberth

	/* SERVER SETUP */

		int server_setup(t_data &data); //AUTHOR: jabenjam
		int addrinfo_setup(t_data &data, char **av); //AUTHOR: jabenjam

	/* SERVER LOOP */

		int server_loop(t_data &data); //AUTHOR: jabenjam
		int poll_setup(t_data &data); //AUTHOR: jabenjam

	/* SERVER CONTROL */

		int command_loop(t_data &data); //AUTHOR: jabenjam

	/* SERVER DISPLAY */

		void put_disconnection(int client_fd); //AUTHOR: jabenjam
		void put_connection(int client_fd); //AUTHOR: jabenjam
		void put_usage(); //AUTHOR: jabenjam
		void put_error(std::string const error); //AUTHOR: jabenjam

	/* USER MANAGEMENT */

		void registration(t_data &data, Users &client); //AUTHOR: jabenjam - thoberth
		void disconnect_user(t_data &data, Users &client); //AUTHOR: jabenjam
		v_Users::iterator find_uid(t_data &data, unsigned int uid); //AUTHOR: jabenjam

	/* ARGUMENT PARSING */

		int parse_arguments(int ac, char **av, t_data &data); //AUTHOR: jabenjam
		bool valid_port(std::string av, t_data &data); //AUTHOR: jabenjam

	/* COMMAND PARSING */

		void command_parsing(t_data &data, Users &client, char buffer[BUFFERSIZE]); //AUTHOR: jabenjam
		void initialize_command_map(t_data &data); //AUTHOR: jabenjam
		std::vector<std::string> parse_line(const std::string &line); //AUTHOR: jabenjam

	/* COMMANDS*/

		void	command_nick(t_data &data, Message &cmd); //AUTHOR: jabenjam
		void	command_user(t_data &data, Message &cmd); //AUTHOR: jabenjam
		void	command_pass(t_data &data, Message &cmd); //AUTHOR: jabenjam
		void	command_die(t_data &data, Message &cmd);  //AUTHOR: jabenjam

	/* UTILS */

		int ft_strlen(const char *str); //AUTHOR: thoberth
		Users &find_client(t_data &data, int fd); //AUTHOR: thoberth et slmt luuuuuuuuuuuuiiiiiii!

	/* DEBUG */

		void print_pollfd(t_data &data); //AUTHOR: jabenjam
		void print_users(t_data &data); //AUTHOR: jabenjam

// TEMPLATES

// DEFINES NUMERIC REPLIES

#define RPL_WELCOME(HOST, NICK, USER) (":" + HOST + " " + "001" + " " + NICK + " :" + "Welcome to the Internet Relay Network " + USER + "\n")

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
