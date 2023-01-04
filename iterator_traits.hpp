#pragma once

#include "utils.hpp"

namespace ft {

	struct input_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	struct output_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:
		typedef typename Iterator::difference_type		ptrdiff_t;
		typedef typename Iterator::value_type			T;
		typedef typename Iterator::pointer				T*;
		typedef typename Iterator::reference			T&;
		typedef typename Iterator::iterator_category	random_access_iterator_tag;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
		typedef typename Iterator::difference_type		ptrdiff_t;
		typedef typename Iterator::value_type			T;
		typedef typename Iterator::pointer				const T*;
		typedef typename Iterator::reference			const T&;
		typedef typename Iterator::iterator_category	random_access_iterator_tag;

	};

} // namespace ft