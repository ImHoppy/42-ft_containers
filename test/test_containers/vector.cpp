#include <iostream>

struct data
{
	int a;
	int b;
};

#ifndef USE_STD
#include "vector.hpp"
using namespace ft;
#else
#include <vector>
using namespace std;
#endif



void old() {
	data d1 = {1, 2};
	data d2 = {3, 4};
	data d3 = {5, 6};
	data d4 = {7, 8};
	{
		// constructors used in the same order as described above:
		::vector<int> first;                                // empty vector of ints
		::vector<int> second (4,100);                       // four ints with value 100
		::vector<int> third (second.begin(),second.end());  // iterating through second
		::vector<int> fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "The contents of fifth are:";
		for (::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Reverse The contents of fifth are:";
		for (::vector<int>::reverse_iterator it = fifth.rbegin(); it != fifth.rend(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		::vector<data> first;
		first.push_back(d1);
		first.push_back(d2);
		first.push_back(d3);
		first.push_back(d4);
		std::cout << "The contents of first are:";
		for (::vector<data>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << ' ' << it->a << ' ' << it->b;
		std::cout << '\n';
		std::cout << "Reverse The contents of first are:";
		for (::vector<data>::reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
			std::cout << ' ' << it->a << ' ' << it->b;
		std::cout << '\n';
	}
}

int	vector_main()
{

	std::cout << "# vector\n";
	old();
	return 0;
}