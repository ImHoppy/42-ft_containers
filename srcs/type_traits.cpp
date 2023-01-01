#include <iostream>
#include <iomanip>
// #include <type_traits>
#include "type_traits.hpp"
#include <cassert>

class A {};

#define assertm(exp, msg) assert(((void)msg, exp))

template <class T>
T f(T i)
{
    assertm(ft::is_integral<T>::value, "Integral required.");
    return i;
}
 
#define SHOW(...) \
    std::cout << std::setw(50) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

void main_type_traits()
{
    std::cout << std::boolalpha;
 
    SHOW( ft::is_integral<float>::value );
    SHOW( ft::is_integral<A>::value );
    SHOW( ft::is_integral<double>::value );
    SHOW( ft::is_integral<int*>::value );
    SHOW( ft::is_integral<int>::value );
    SHOW( ft::is_integral<unsigned int>::value );
    SHOW( ft::is_integral<signed int>::value );
    SHOW( ft::is_integral<const int>::value );
    SHOW( ft::is_integral<long>::value );
    SHOW( ft::is_integral<long long>::value );
    SHOW( ft::is_integral<bool>::value );
    SHOW( ft::is_integral<char>::value );
    SHOW( ft::is_integral<volatile const char>::value );
    SHOW( f(123) );
}