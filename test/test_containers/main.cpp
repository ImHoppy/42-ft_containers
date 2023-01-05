#include <cstdlib>

void vector_main() {};
void list_main() {};
void map_main() {};
void stack_main() {};
void queue_main() {};
void set_main() {};
void main_type_traits();

int	main(int ac, char **av)
{
	int flags = 0;
	if (ac > 1)
	{
		flags = atoi(av[1]);
		if (flags < 0)
			return 1; 
	}
	if (not flags || flags & 1)
		vector_main();
	if (not flags || flags & 2)
		map_main();
	if (not flags || flags & 4)
		stack_main();
	if (not flags || flags & 8)
	{
		main_type_traits();
	}
	if (not flags || flags & 16)
		set_main();
	return 0;
}