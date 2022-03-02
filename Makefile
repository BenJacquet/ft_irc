NAME = ircserv

SRCS = srcs/main.cpp\
		srcs/utils.cpp\
		srcs/fd_management.cpp\
		srcs/io_operations.cpp\
		srcs/server_setup.cpp\
		srcs/server_loop.cpp\
		srcs/server_display.cpp\
		srcs/arg_parsing.cpp\
		srcs/command_parsing.cpp

INCS = incs/ft_irc.hpp

OBJS = $(SRCS:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(OBJS) : $(INCS)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re