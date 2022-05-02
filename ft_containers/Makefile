NAME = containers_test

SRCS = main.cpp

INCS =  iterator/iterator.hpp\
		iterator/iterator_traits.hpp\
		iterator/bidirectional_iterator.hpp\
		iterator/random_access_iterator.hpp\
		vector/vector.hpp\
		utils/utils.hpp

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