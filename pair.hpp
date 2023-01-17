#pragma once

#include "utils.hpp"
#include <utility>

namespace ft
{
	temaplate<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template<typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;
		
		// Default constructor
		pair() : first(T1()), second(T2()) {};
		// nitialization constructor
		pair(const first_type& a, const second_type& b) : first(a), second(b) {};
		// Copy constructor
		template<clas U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {};

		pair& operator=(const pair& pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}

		// Compare two pairs
		template<class U, class V>
		friend bool operator==(const pair<U, V>& lhs, const pair<U, V>& rhs);
		template<class U, class V>
		friend bool operator!=(const pair<U, V>& lhs, const pair<U, V>& rhs);
		template<class U, class V>
		friend bool operator<(const pair<U, V>& lhs, const pair<U, V>& rhs);
		template<class U, class V>
		friend bool operator<=(const pair<U, V>& lhs, const pair<U, V>& rhs);
		template<class U, class V>
		friend bool operator>(const pair<U, V>& lhs, const pair<U, V>& rhs);
		template<class U, class V>
		friend bool operator>=(const pair<U, V>& lhs, const pair<U, V>& rhs);
	};

	template<class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first != rhs.first || lhs.second != rhs.second);
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first && lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first <= rhs.first && lhs.second <= rhs.second);
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first > rhs.first && lhs.second > rhs.second);
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first >= rhs.first && lhs.second >= rhs.second);
	}

} // namespace ft
