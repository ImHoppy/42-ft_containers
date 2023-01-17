#pragma once

#include "pair.hpp"
#include "utils.hpp"
#include "rbtree.hpp"
#include <memory>

namespace ft
{
	template <class Key,
			  class T,
			  class Compare = ft::less<Key>,
			  class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		class value_compare : ft::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};
		typedef Alloc allocator_type;
		typedef typename Alloc::reference reference;
		typedef typename Alloc::const_reference const_reference;
		typedef typename Alloc::pointer pointer;
		typedef typename Alloc::const_pointer const_pointer;
		typedef rb_iterator<value_type, key_compare> iterator;
		typedef rb_iterator<const value_type, key_compare> const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
	};
} // namespace ft
