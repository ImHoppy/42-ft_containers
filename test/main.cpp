#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sys/time.h>
#include "color.hpp"
#include <stdlib.h>

struct TestUnit {
	bool	on;
	struct	countTests {
		countTests() : count(0), countTotal(0) {};
		int		count;
		int		countTotal;
	};
	countTests	all;
	countTests	current;
	bool	result;

	TestUnit() : on(false), all(), current(), result(true) {};
	void	start() {
		on = true;
		result = true;
	}

	void	add() {
		if (not on) return;

		++current.countTotal;
		current.count += result;
		std::cout << "[ " << (result ? SetColor(fg::green, "OK") : SetColor(fg::red, "KO"))	<< " ]    ";
		result = true;
	}

	void	end() {
		if (not on) return;

		on = false;
		++all.countTotal;
		result = current.count == current.countTotal;
		all.count += result;
		
		std::cout << "| ";
		std::cout << (result ? SetColor(fg::green, "OK") : SetColor(fg::red, "KO")) << " ";
		std::cout << current.count << "/" << current.countTotal;
		std::cout << "\n\n";

		current.count = 0;
		current.countTotal = 0;
	}
};

const char *test_flags[] = {"vector", "map", "stack", "utils", "set"};

int	parseArgs(int ac, char** av)
{
	int	flag = 0;
	
	for (int i = 1; i < ac; ++i) {
		std::string arg(av[i]);
		for (unsigned long j = 0; j < sizeof(test_flags) / sizeof(test_flags[0]); ++j) {
			if (arg == test_flags[j]) {
				flag |= (1 << j);
				break;
			}
		}
	}
	return flag;
}

int main(int ac, char** av)
{
	std::string flag = SSTR(parseArgs(ac, av));

	std::string stl_exec = "./test_containers/std_containers " + flag + " | tee output_std.txt";
	std::string ft_exec = "./test_containers/ft_containers " + flag + " | tee output_ft.txt";

	TestUnit test;

	struct timeval starting_time;
	struct timeval ending_time;

	gettimeofday(&starting_time, NULL);

	FILE* stream1 = popen(stl_exec.c_str(), "r");

	gettimeofday(&ending_time, NULL);
	std::cout << "STD: " << (ending_time.tv_sec - starting_time.tv_sec) * 1000 + (ending_time.tv_usec - starting_time.tv_usec) / 1000 << "ms " << ((ending_time.tv_usec - starting_time.tv_usec) % 1000) << "us\n";

	gettimeofday(&starting_time, NULL);
	
	FILE* stream2 = popen(ft_exec.c_str(), "r");
	
	gettimeofday(&ending_time, NULL);

	std::cout << "FT: " << (ending_time.tv_sec - starting_time.tv_sec) * 1000 + (ending_time.tv_usec - starting_time.tv_usec) / 1000 << "ms " << ((ending_time.tv_usec - starting_time.tv_usec) % 1000) << "us\n";

	// Read the output of the two executables line by line
	char line1[1024] = {};
	char line2[1024] = {};
	bool freeze1 = false;
	bool freeze2 = false;

	while ((freeze1 || fgets(line1, 1024, stream1)) && (freeze2 || fgets(line2, 1024, stream2))) {
		// std::cout << std::boolalpha << "Freeze: " << freeze1 << "Line1: " << line1 << std::endl;
		// std::cout << std::boolalpha << "Freeze: " << freeze2 << "Line2: " << line2 << std::endl;
		if (strlen(line1) == 1 && strlen(line2) == 1) {
			continue;
		}

		else if (line1[0] == '#' && line2[0] == '#' && strcmp(line1, line2) == 0) {
			if (test.on)
				test.end();
			test.start();
			std::cout << style::bold << fg::magenta << line1 << style::reset << std::endl;
			freeze1 = false;
			freeze2 = false;
		}
		else if (line1[0] == '#')
		{
			test.result = false;
			test.add();
			freeze1 = true;
		}
		else if (line2[0] == '#')
		{
			test.result = false;
			test.add();
			freeze2 = true;
		}
		else if (strcmp(line1, line2) != 0) {
			test.result = false;
			test.add();
			std::cout << '\n';
			std::cout << SetColor(fg::blue, "Expected: ") << std::setw(5) << line1;
			std::cout << SetColor(fg::blue, "Got: ") << std::setw(10) << line2;
			std::cout << '\n';
		}
		else 
			test.add();
	}
	
	if (test.on)
		test.end();
	if (strcmp(line1, line2) != 0 || fgets(line1, 1024, stream1) || fgets(line2, 1024, stream2)) {
		std::cout << bg::red << fg::white << "Outputs have different number of lines" << style::reset << std::endl;
	}
	else {
		std::cout << bg::green << fg::white << "Outputs have the same number of lines" << style::reset << std::endl;
	}

	fg::type resultColor = (test.all.count == test.all.countTotal ? fg::green : fg::red);
	std::cout << resultColor << test.all.count 
		<< "/" << resultColor << test.all.countTotal << style::reset << std::endl;

	pclose(stream1);
	pclose(stream2);


	// Speed time test

	system("./time_test");

	return 0;
}