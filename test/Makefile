NAME		= ft_containers_tester

SOURCES		= main.cpp
OBJECTS		= $(SOURCES:.cpp=.o)
DEPS		= $(OBJECTS:.o=.d)

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -MMD -MP -I.  -std=c++98


$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)

all: $(NAME)
	$(MAKE) FT=1 --directory=test_containers
	$(MAKE) clean FT=1 --silent --directory=test_containers
	$(MAKE) STD=1 --directory=test_containers

clean:
	rm -rf $(OBJECTS)
	rm -rf output_ft.txt output_std.txt
	$(MAKE) fclean FT=1 --directory=test_containers
	$(MAKE) fclean STD=1 --directory=test_containers

fclean: clean
	rm -f $(NAME)
	rm -rf $(DEPS)

re: fclean
	$(MAKE) all

-include $(DEPS)

.DEFAULT_GOAL = all
.PHONY: all clean fclean re
