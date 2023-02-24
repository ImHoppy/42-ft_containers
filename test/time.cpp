#include "../map.hpp"
#include <map>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "../vector.hpp"
#include <vector>
#include "../utils.hpp"
#include <stack>
#include "../stack.hpp"
#include <set>
#include "../set.hpp"
#include <sys/time.h>

# define CRED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

inline int getMs(struct timeval start, struct timeval end)
{
	return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}

void log(std::string container, int ft_time, int std_time)
{
	if (ft_time < std_time)
		std::cout << BLUE << "ft::" << container << " is " << (float)std_time / ft_time << " times faster than std::" << container;
	else
	{
		if (ft_time/ std_time > 20)
			std::cout << CRED;
		else if (ft_time/ std_time > 15)
			std::cout << YELLOW;
		else
			std::cout << GREEN;
		std::cout << "std::" << container << " is " << (float)ft_time / std_time << " times faster than ft::" << container;
	}
	std::cout << RESET << std::endl;
}

int main()
{
	ft::map<int, int> m;
	std::map<int, int> m2;
	srand(time(NULL));
	struct timeval start, end;
	int ft_time = 0;
	int std_time = 0;

	std::vector <int> v;
	for (int i = 0; i < 100000; i++)
	{
		int r = rand() % 100000;
		v.push_back(r);
	}
	std::cout << "-------------------MAP-------------------" << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		m.insert(ft::make_pair(v[i], v[i]));
	}
	gettimeofday(&end, NULL);
	std::cout << "##################### INSERT #####################" << std::endl;
	ft_time = getMs(start, end);
	std::cout << "ft::map: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		m2.insert(std::make_pair(v[i], v[i]));
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::map: " << std_time << std::endl;

	log("map", ft_time, std_time);

	std::cout << "##################### FIND #####################" << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		m.find(v[i]);
	}
	gettimeofday(&end, NULL);
	ft_time = getMs(start, end);
	std::cout << "ft::map :" << ft_time << std::endl;

	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		m2.find(v[i]);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::map: " << std_time << std::endl;

	log("map", ft_time, std_time);
	
	std::cout << "##################### COPY #####################" << std::endl;
	gettimeofday(&start, NULL);
	ft::map<int, int> m3(m);
	gettimeofday(&end, NULL);
	ft_time = getMs(start, end);
	std::cout << "ft::map :" << ft_time << std::endl;

	gettimeofday(&start, NULL);
	std::map<int, int> m4(m2);
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::map: " << std_time << std::endl;

	log("map", ft_time, std_time);

	std::cout << "##################### ERASE #####################" << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		m.erase(v[i]);
	}
	gettimeofday(&end, NULL);
	ft_time = getMs(start, end);
	std::cout << "ft::map: " << ft_time << std::endl;

	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		m2.erase(v[i]);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::map: " << std_time << std::endl;

	log("map", ft_time, std_time);
	
	std::cout << "-------------------SET-------------------" << std::endl;

	ft::set<int> s;
	std::set<int> s2;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		s.insert(v[i]);
	}
	gettimeofday(&end, NULL);
	std::cout << "##################### INSERT #####################" << std::endl;
	ft_time = getMs(start, end);
	std::cout << "ft::set: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		s2.insert(v[i]);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::set: " << std_time << std::endl;

	log("set", ft_time, std_time);
	
	std::cout << "##################### FIND #####################" << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		s.find(v[i]);
	}
	gettimeofday(&end, NULL);
	ft_time = getMs(start, end);
	std::cout << "ft::set: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		s2.find(v[i]);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::set: " << std_time << std::endl;

	log("set", ft_time, std_time);
	
	std::cout << "##################### ERASE #####################" << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		s.erase(v[i]);
	}
	gettimeofday(&end, NULL);
	std::cout << "ft::set: " << getMs(start, end) << std::endl;	
	ft_time = getMs(start, end);
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		s2.erase(v[i]);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::set: " << std_time << std::endl;

	log("set", ft_time, std_time);

	std::cout << "-------------------VECTOR-------------------" << std::endl;

	ft::vector<int> vec;
	std::vector<int> vec2;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		vec.push_back(v[i]);
	}
	gettimeofday(&end, NULL);
	std::cout << "##################### INSERT #####################" << std::endl;
	ft_time = getMs(start, end);
	std::cout << "ft::vector: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		vec2.push_back(v[i]);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::vector: " << std_time << std::endl;

	log("vector", ft_time, std_time);


	std::cout << "##################### COPY #####################" << std::endl;
	gettimeofday(&start, NULL);
	ft::vector<int> vec3(vec);
	gettimeofday(&end, NULL);
	ft_time = getMs(start, end);
	std::cout << "ft::vector: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	std::vector<int> vec4(vec2);
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::vector: " << std_time << std::endl;

	log("vector", ft_time, std_time);


	std::cout << "##################### ERASE #####################" << std::endl;
	gettimeofday(&start, NULL);
	 for (int i = 0; i < 10000; i++)
	{
		vec.erase(vec.begin() + i);
	} 
	gettimeofday(&end, NULL);
	ft_time = getMs(start, end);
	std::cout << "ft::vector: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 10000; i++)
	{
		vec2.erase(vec2.begin() + i);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::vector: " << std_time << std::endl;

	log("vector", ft_time, std_time);

	
	std::cout << "-------------------STACK-------------------" << std::endl;

	ft::stack<int> st;
	std::stack<int> st2;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		st.push(v[i]);
	}
	gettimeofday(&end, NULL);
	std::cout << "##################### PUSH #####################" << std::endl;
	ft_time = getMs(start, end);
	std::cout << "ft::stack: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		st2.push(v[i]);
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::stack: " << std_time << std::endl;
	if (ft_time < std_time)
		std::cout << "ft::stack is " << (float)std_time / ft_time << " times faster than std::stack" << std::endl;
	else
	{
		if (ft_time/ std_time > 20)
			std::cout << CRED;
		else if (ft_time/ std_time > 15)
			std::cout << YELLOW;
		else
			std::cout << GREEN;
		std::cout << "std::stack is " << (float)ft_time / std_time << " times faster than ft::stack" << std::endl;
		std::cout << RESET;
	}
	std::cout << "##################### POP #####################" << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		st.pop();
	}
	gettimeofday(&end, NULL);
	ft_time = getMs(start, end);
	std::cout << "ft::stack: " << ft_time << std::endl;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 100000; i++)
	{
		st2.pop();
	}
	gettimeofday(&end, NULL);
	std_time = getMs(start, end);
	std::cout << "std::stack: " << std_time << std::endl;

	log("stack", ft_time, std_time);


	std::cout << "-------------------END-------------------" << std::endl;
	return 0;
}