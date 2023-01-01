#pragma once

namespace ft
{

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
		constexpr operator value_type() const noexcept { return value; }
		constexpr value_type operator()() const noexcept { return value; }
	};
	template<typename _Tp, _Tp __v>
		constexpr _Tp integral_constant<_Tp, __v>::value;
	using true_type = integral_constant<bool, true>;
	using false_type = integral_constant<bool, false>;

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
	
	template<>
		struct is_integral_helper<char16_t>
		: public true_type { };
	
	template<>
		struct is_integral_helper<char32_t>
		: public true_type { };
	
	template<>
		struct is_integral_helper<short>
		: public true_type { };
	
	template<>
		struct is_integral_helper<unsigned short>
		: public true_type { };
	
	#include <iostream>
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
	using remove_cv_type = typename remove_cv<T>::type;

	template<typename T>
	struct is_integral
	: public is_integral_helper<remove_cv_type<T>>::type
	{ };

	#include <iostream>

	// is_integral_v
	template< class T >
	inline bool is_integral_v = is_integral<T>::value;


} // namespace ft
