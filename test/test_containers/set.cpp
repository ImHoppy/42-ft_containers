#include <iostream>
#include <string>
#ifndef USE_STD
#include "set.hpp"
using namespace ft;
#else
#include <set>
using namespace std;
#endif



void set_main() {
	std::cout << "# Set\n";
	set<char>	mp;

	mp.insert('a');
	mp.insert('b');
	mp.insert('c');
	mp.insert('d');
	for (set<char>::iterator it = mp.begin(); it != mp.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}