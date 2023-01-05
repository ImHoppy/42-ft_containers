#include <iostream>
#include <iomanip>
#include <cassert>

#ifndef USE_STD
#include "type_traits.hpp"
using namespace ft;
#else
#include <type_traits>
using namespace std;
#endif


class A {};

 
#define SHOW(...) \
    std::cout << std::setw(50) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

void main_type_traits()
{
    std::cout << std::boolalpha;
	std::cout << "# is_integral\n";
	// False
	SHOW( ::is_integral<A>::value );
    SHOW( ::is_integral<float>::value );
    SHOW( ::is_integral<double>::value );
    SHOW( ::is_integral<int*>::value );
    SHOW( ::is_integral<const float>::value );
    SHOW( ::is_integral<void>::value );
	// True
    SHOW( ::is_integral<bool>::value );
    SHOW( ::is_integral<int>::value );
    SHOW( ::is_integral<short>::value );
    SHOW( ::is_integral<unsigned int>::value );
    SHOW( ::is_integral<signed int>::value );
    SHOW( ::is_integral<const int>::value );
    SHOW( ::is_integral<long>::value );
    SHOW( ::is_integral<long long>::value );
    SHOW( ::is_integral<unsigned long>::value );
    SHOW( ::is_integral<signed char>::value );
    SHOW( ::is_integral<unsigned char>::value );
    SHOW( ::is_integral<const char>::value );
    SHOW( ::is_integral<volatile const char>::value );
}