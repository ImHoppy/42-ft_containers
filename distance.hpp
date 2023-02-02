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
}