
SOURCES		= main.cpp type_traits.cpp vector.cpp
OBJECTS		= $(SOURCES:.cpp=.o)
DEPS		= $(OBJECTS:.o=.d)

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -MMD -MP -I../.. -g3


ifdef STD
	NAME		= std_containers
	CXXFLAGS += -DUSE_STD=1 -std=c++11
else
	NAME		= ft_containers
	CXXFLAGS	+= -std=c++98
endif

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)

all: $(NAME)

clean:
	rm -rf $(OBJECTS)
	rm -rf $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

-include $(DEPS)

.DEFAULT_GOAL = all
.PHONY: all clean fclean re
