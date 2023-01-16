#include <iostream>
#include <string>
struct data
{
	int a;
	int b;
};

std::ostream &operator<<(std::ostream &os, data &obj);

#ifndef USE_STD
#include "stack.hpp"
#include "vector.hpp"

using namespace ft;
#else
#include <stack>
#include <vector>
using namespace std;
#endif

#include <deque>

void stack_main() {
	std::cout << "# stack\n";
	stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	std::deque<int> mydeque (3,100);
	vector<int> myvector (2,200);

	stack<int> first;
	stack<int, std::deque<int> > second (mydeque);

	stack<int,vector<int> > third;
	stack<int,vector<int> > fourth (myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';
	{
		stack<int> mystack;
		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		std::cout << "mystack.top() is now " << mystack.top() << '\n';
	}
	stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';

}