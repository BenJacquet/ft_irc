NAME = ircserv

SRCS = srcs/main.cpp\
		srcs/utils.cpp\
		srcs/fd_management.cpp\
		srcs/user_management.cpp\
		srcs/io_operations.cpp\
		srcs/server_setup.cpp\
		srcs/server_loop.cpp\
		srcs/server_control.cpp\
		srcs/server_display.cpp\
		srcs/argument_parsing.cpp\
		srcs/command_parsing.cpp\
		srcs/commands.cpp\
		srcs/debug.cpp\
		class/Message.cpp\
		class/Users.cpp\
		class/Chan.cpp\
		srcs/crypto.cpp\
		srcs/commands/privmsg.cpp\
		srcs/commands/join.cpp\
		srcs/commands/part.cpp\
		srcs/commands/mode.cpp\
		srcs/commands/away.cpp\
		srcs/commands/nick.cpp\
		srcs/commands/pass.cpp\
		srcs/commands/user.cpp\
		srcs/commands/oper.cpp\
		srcs/commands/ping.cpp\
		srcs/commands/die.cpp\
		srcs/commands/kick.cpp

INCS = incs/ft_irc.hpp\
		class/Message.hpp\
		class/Users.hpp\
		class/Chan.hpp

OBJS = $(SRCS:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98

all : $(NAME)

$(OBJS) : $(INCS)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME) log.txt

re : fclean all

.PHONY : all clean fclean re