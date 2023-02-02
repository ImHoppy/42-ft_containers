#pragma once

#include "iterator_traits.hpp"
#include <iterator>

namespace ft
{
	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	distance_tag(InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}

	template <typename RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type
	distance_tag(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
	{
		return last - first;
	}

	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return distance_tag(first, last, iterator_category(first));
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

}