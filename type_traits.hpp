#pragma once
#include <uchar.h>

namespace ft
{

	template< bool, typename >
	struct enable_if { };

	template< typename T >
	struct enable_if<true, T> { typedef T type; };

	template< class T > struct remove_cv					{ typedef T type; };
	template< class T > struct remove_cv<const T>			{ typedef T type; };
	template< class T > struct remove_cv<volatile T>		{ typedef T type; };
	template< class T > struct remove_cv<const volatile T>	{ typedef T type; };

	template< typename T, T V >
	struct integral_constant
	{
		typedef T value_type;
		typedef integral_constant<T, V> type;
		static const T value = V;
		operator bool() const { return value; }
	};

	// using true_type = integral_constant<bool, true>;
	// using false_type = integral_constant<bool, false>;
	struct true_type : public integral_constant<bool, true> { };
	struct false_type : public integral_constant<bool, false> { };

	template<typename>
		struct is_integral_helper
		: public false_type { };
	
	template<>
		struct is_integral_helper<bool>
		: public true_type { };
	
	template<>
		struct is_integral_helper<char>
		: public true_type { };
	
	template<>
		struct is_integral_helper<signed char>
		: public true_type { };
	
	template<>
		struct is_integral_helper<unsigned char>
		: public true_type { };
	
	// Duplicate char16_t == unsigned short
/* 	template<>
		struct is_integral_helper<char16_t>
		: public true_type { }; */
	
	// Duplicate char32_t == unsigned int
/* 	template<>
		struct is_integral_helper<char32_t>
		: public true_type { }; */
	
	template<>
		struct is_integral_helper<short>
		: public true_type { };
	
	template<>
		struct is_integral_helper<unsigned short>
		: public true_type { };
	
	template<>
		struct is_integral_helper<int>
		: public true_type { };
	
	template<>
		struct is_integral_helper<unsigned int>
		: public true_type { };
	
	template<>
		struct is_integral_helper<long>
		: public true_type { };
	
	template<>
		struct is_integral_helper<unsigned long>
		: public true_type { };
	
	template<>
		struct is_integral_helper<long long>
		: public true_type { };
	
	template<>
		struct is_integral_helper<unsigned long long>
		: public true_type { };

	template<typename T>
	struct is_integral
	: public is_integral_helper<typename remove_cv<T>::type >::type
	{ };


} // namespace ft
