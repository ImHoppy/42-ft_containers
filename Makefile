NAME		= ft_container_tester

SOURCES		= srcs/main.cpp
OBJECTS		= $(SOURCES:.cpp=.o)
DEPS		= $(OBJECTS:.o=.d)

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -MMD -MP -I. -std=c++98 
# CXXFLAGS	= -Wall -Wextra -Werror -MMD -MP -I. -std=c++20 -g3


$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)

all: $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

-include $(DEPS)

.DEFAULT_GOAL = all
.PHONY: all clean fclean re
