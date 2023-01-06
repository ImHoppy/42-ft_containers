#include <iostream>

struct data
{
	int a;
	int b;
};

std::ostream& operator<<(std::ostream& os, data& obj)
{
	os << "a: " << obj.a << "\tb: " << obj.b;
	return os;
}

#ifndef USE_STD
#include "vector.hpp"
using namespace ft;
#else
#include <vector>
using namespace std;
#endif


template <typename T>
inline void print_vector_size(::vector<T>& vector)
{
	std::cout << "vector size: " << vector.size() << "\t";
	std::cout << "vector capacity: " << vector.capacity() << "\t";
	std::cout << "vector max size: " << vector.max_size() << "\t";
	std::cout << "\n";
}


template <typename T>
inline void print_vector_content(::vector<T>& vec)
{
	for (typename ::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << " |";
	for (typename ::vector<T>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
		std::cout << ' ' << *it;
	
	std::cout << '\n';
}

void old() {
	data d1 = {1, 2};
	data d2 = {3, 4};
	data d3 = {5, 6};
	data d4 = {7, 8};
	{
		// constructors used in the same order as described above:
		::vector<int> first;                                // empty vector of ints
		print_vector_size(first);
		::vector<int> second (4,100);                       // four ints with value 100
		print_vector_size(second);
		::vector<int> third (second.begin(),second.end());  // iterating through second
		print_vector_size(third);
		::vector<int> fourth (third);                       // a copy of third
		print_vector_size(fourth);\

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		print_vector_content(first);
		print_vector_content(second);
		print_vector_content(third);
		print_vector_content(fourth);
		print_vector_content(fifth);
	}
 	{
		::vector<data> first;
		print_vector_size(first);
		first.push_back(d1);
		print_vector_size(first);
		first.push_back(d2);
		print_vector_size(first);
		first.push_back(d3);
		print_vector_size(first);
		first.push_back(d4);
		print_vector_size(first);
		first.pop_back();
		print_vector_content(first);
		print_vector_size(first);
	}
}

void	assign_test()
{
	vector<int> first;
	vector<int> second;
	vector<int> third;
	
	first.assign (7,100);
	print_vector_size(third);
	print_vector_content(third);
	
	vector<int>::iterator it;
	it=first.begin()+1;
	print_vector_size(third);
	print_vector_content(third);
	
	second.assign (it,first.end()-1);
	print_vector_size(third);
	print_vector_content(third);
	
	int myints[] = {1776,7,4};
	print_vector_size(third);
	print_vector_content(third);

	third.assign (myints,myints+3);
	print_vector_size(first);
	print_vector_content(first);
	print_vector_size(second);
	print_vector_content(second);
	print_vector_size(third);
	print_vector_content(third);
	
}

void	resize_test()
{
	::vector<int> myvector;
	
	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);
	
	myvector.resize(5);
	print_vector_size(myvector);
	print_vector_content(myvector);

	myvector.resize(8,100);
	print_vector_size(myvector);
	print_vector_content(myvector);

	myvector.resize(12);
	print_vector_size(myvector);
	print_vector_content(myvector);
}

void	insert_test()
{
	vector<int> myvector (3,100);
	vector<int>::iterator it;
	print_vector_size(myvector);
	print_vector_content(myvector);
	
	it = myvector.begin();
	it = myvector.insert ( it , 200 );
	print_vector_size(myvector);
	print_vector_content(myvector);
	
	myvector.insert (it,2,300);
	print_vector_size(myvector);
	print_vector_content(myvector);
	
	// "it" no longer valid, get a new one:
	it = myvector.begin();
	
	vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());
	print_vector_size(myvector);
	print_vector_content(myvector);
	
	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);
	print_vector_size(myvector);
	print_vector_content(myvector);

	const int bits[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
	::vector<int> v(bits, bits + 11 );
	print_vector_size(v);
	print_vector_content(v);
	v.insert(v.begin() + 3, 3);
	print_vector_size(v);
	print_vector_content(v);
}

#include <iterator>
#include <sstream>
#include <iterator>
void input_iterator()
{
    vector<int> v;
	std::stringstream text("1\n2\n3\n4\n5\n6\n7\n8\n9\n10");

	std::istream_iterator<int>	start(text);
	std::istream_iterator<int>	last;

	v.insert(v.begin(), start, last);
	
	std::cout << ::distance(start, last) << '\n';
	print_vector_size(v);
	print_vector_content(v);
}

int	vector_main()
{

	std::cout << "# vector\n";
	// old();
	// resize_test();
	// insert_test();
	input_iterator();


	return 0;
}