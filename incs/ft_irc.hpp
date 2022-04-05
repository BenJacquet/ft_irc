/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:26:47 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/05 16:56:16 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <fstream>
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

#include "../class/Chan.hpp"
#include "../class/Users.hpp"
#include "../class/Message.hpp"

class Message;
class Users;
class Chan;

// DEFINES

#define BUFFERSIZE 4096

#define TIMEOUT 300

#define BACKLOG 10

#define COUT(COLOR, DATA) (std::cout << COLOR << DATA << "\r\n" << RESET)
#define CERR(COLOR, DATA) (std::cerr << COLOR << DATA << "\r\n" << RESET)

// TYPEDEFS

typedef std::vector<struct pollfd>			v_pollfds;
typedef std::vector<Users> 					v_Users;
typedef std::vector<Chan> 					v_Chan;
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
	v_Chan				chans;			// vector de Chan existantes
	m_Commands			commands;		// map qui contient en key->string de la commande et value->fonction pointeur
	std::string			password;		// password admin
	long				salt;			// sel pour les mdp
}						t_data;

// PROTOTYPES

	/* FD MANAGEMENT */

		v_pollfds::iterator find_fd(t_data &data, int fd);
		void remove_fd(t_data &data, int fd);
		void add_fd(t_data &data, int fd);
		int new_connection(t_data &data);

	/* IO OPERATIONS */

		void io_loop(t_data &data, Users &client);
		int receive_packets(t_data &data, Users &client);
		int send_packets(Users &client, std::string to_send);
		std::string create_reply(t_data &data, Users *client, int code, std::string arg);
		void log_coms(Users &client, std::string &to_log, bool out);

	/* SERVER SETUP */

		int server_setup(t_data &data);
		int addrinfo_setup(t_data &data, char **av);

	/* SERVER LOOP */

		int server_loop(t_data &data);
		int poll_setup(t_data &data);

	/* SERVER CONTROL */

		int command_loop(t_data &data);

	/* SERVER DISPLAY */

		void put_usage();
		void put_error(std::string const error);
		void server_shutdown();

	/* USER MANAGEMENT */

		void	registration(t_data &data, Users *client);
		void	disconnect_user(t_data &data, Users &client);
		void	check_nick(t_data &data, Users &user, std::string nick);
		bool	authenticate_user(t_data &data, Users *client, std::string nick);
		void	replace_user(t_data &data, Users &user);

	/* ARGUMENT PARSING */

		int parse_arguments(int ac, char **av, t_data &data);
		bool valid_port(std::string av, t_data &data);

	/* COMMAND PARSING */

		void command_parsing(t_data &data, Users &client, std::string buffer);
		void initialize_command_map(t_data &data);
		std::vector<std::string> parse_line(const std::string &line);

	/* COMMANDS*/

		void	command_nick(t_data &data, Message &cmd);
		void	command_user(t_data &data, Message &cmd);
		void	command_pass(t_data &data, Message &cmd);
		void	command_die(t_data &data, Message &cmd);
		void	command_oper(t_data &data, Message &cmd);
		void	command_ping(t_data &data, Message &cmd);
		void	command_privmsg(t_data &data, Message &cmd);
		void	channel_privmsg(Chan &chan, Users &user, std::string content);
		void	join(t_data &data, Users & creator, std::string name_chan);
		void	join_parsing(t_data &data, Message &cmd);
		void	join_msg(Users &to_add, Chan &chan, bool isnewone);
		void	RPL_353_366(Users &usr, Chan &chan);
		void	part_parsing(t_data &data, Message &cmd);
		void	who_command_parsing(t_data &data, Message &cmd);
		void	who_parsing(t_data &data, Message &cmd);
		void	whois_parsing(t_data &data, Message &cmd);
		void	whowas_parsing(t_data &data, Message &cmd);
		void	mode_parsing(t_data &data, Message &cmd);
		void	user_mode(t_data &data, Users &client, std::string content);
		void	chan_mode(t_data &data, Chan &chan,Users &client, std::string content);
		void	away_parsing(t_data &data, Message &cmd);

	/* UTILS */

		int ft_strlen(const char *str);
		v_Users::iterator find_client_fd(t_data &data, int fd);
		v_Users::iterator find_client_uid(t_data &data, unsigned int uid);
		v_Users::iterator find_client_nick(t_data &data, std::string nick);
		Chan*	is_chan_exist(t_data &data, std::string args);
		std::string	encrypt_data(long salt, std::string to_encrypt);
		std::string get_ip_string(sockaddr_in6 address);
		void remove_carriage(std::string &data);

	/* DEBUG */

		void print_pollfd(t_data &data);
		void print_users(t_data &data);

// EXTERN GLOBALS

extern time_t			g_start;
extern std::ofstream	g_log;

// TEMPLATES

// DEFINES NUMERIC REPLIES

#define UPDATE_NICK(FULL, NICK) (":" + FULL + " NICK " + NICK)
#define PING(HOST) ("PING " + HOST)

#define RPL_WELCOME(FULL) (":Welcome to the Internet Relay Network " + FULL) // 001
#define RPL_UMODEIS(MODE) (":" + MODE) // 221
#define RPL_CHANNELMODEIS(MODE) (MODE) //324
#define RPL_YOUREOPER() (":You are now an IRC operator") // 381

#define ERR_NONICKNAMEGIVEM() (":No nickname given") // 431
#define ERR_ERRONEUSNICKNAME(NICK) (NICK + " :Erroneous nickname") // 432
#define ERR_NICKNAMEINUSE(NICK) (NICK + " :Nickname is already in use") // 433
#define ERR_NEEDMOREPARAMS(CMD) (CMD + " :Not enough parameters") // 461
#define ERR_ALREADYREGISTERED() (":Unauthorized command (already registered)") // 462
#define ERR_PASSWDMISMATCH() (":Password incorrect") // 464
#define ERR_NOPRIVILEGE() (":Permission Denied- You're not an IRC operator") // 481
#define ERR_UMODEUNKNOWNFLAG() (":Unknown MODE flag") // 501
#define ERR_USERMISMATCH() (":Cannot change mode for other users") // 502

#define NICK_CHARSET() ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_[]{}\\`|")

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
