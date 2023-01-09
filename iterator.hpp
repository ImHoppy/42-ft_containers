#pragma once
#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft
{
	
	template<typename InputIterator>
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

	template<typename RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type
	distance_tag(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
	{
		return last - first;
	}


	template<typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return distance_tag(first, last, iterator_category(first));
	}

	template< class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T& >
	struct iterator
	{
		typedef Distance	difference_type;
		typedef T			value_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template< typename Iterator >
	class random_access_iterator : public iterator<std::random_access_iterator_tag, Iterator>
	{
		protected:
			typedef iterator<std::random_access_iterator_tag, Iterator>	_traits_type;

			typename _traits_type::pointer	_current;

		public:
			typedef Iterator									iterator_type;
			typedef typename _traits_type::iterator_category	iterator_category;
			typedef typename _traits_type::value_type			value_type;
			typedef typename _traits_type::difference_type		difference_type;
			typedef typename _traits_type::pointer				pointer;
			typedef typename _traits_type::reference			reference;

			pointer	base() const { return _current; };

			random_access_iterator()
				: _current(NULL) { }
			explicit random_access_iterator(const pointer& it)
				: _current(it) { }
			// explicit random_access_iterator(const Iterator& it)
			// 	: _current(&it) { }

			// Allow conversion from non-const to const iterator
			template<typename Iter>
			random_access_iterator(const random_access_iterator<Iter>& other)
				: _current(other.base()) { }

			// Copy assignment operator
			random_access_iterator &operator=(const random_access_iterator& other)
			{
				if (this == &other)
					return (*this);
				this->_current = other._current;
				return (*this);
			}

			// Forward iterator
			reference	operator*(void) const { return (*_current); }
			pointer		operator->() const { return _current; }

			random_access_iterator&	operator++() { ++_current; return *this; }
			random_access_iterator	operator++(int) { random_access_iterator tmp(*this); ++_current; return tmp; }

			// Bidirectional iterator
			random_access_iterator&	operator--() { --_current; return *this; }
			random_access_iterator	operator--(int) { random_access_iterator tmp(*this); --_current; return tmp; }

			// Random access iterator
			reference	operator[](difference_type n) const { return _current[n]; }

			random_access_iterator&	operator+=(difference_type n) { _current += n; return *this; }
			random_access_iterator	operator+(difference_type n) const { return random_access_iterator(_current + n); }

			random_access_iterator&	operator-=(difference_type n) { _current -= n; return *this; }
			random_access_iterator	operator-(difference_type n) const { return random_access_iterator(_current - n); }


			difference_type operator +(random_access_iterator b) { return (_current + b._current); }; // a + b
			difference_type operator -(random_access_iterator b) { return (_current - b._current); }; // a - b

			// operator random_access_iterator<const T> () const
			// { return (random_access_iterator<const T>(this->_elem)); }

	};

	// Comparison const It & nonconst It operators (forward iterator)
	template< typename LeftIt, typename RightIt >
		inline bool	operator==
			(const random_access_iterator<LeftIt>& lhs, const random_access_iterator<RightIt>& rhs)
		{ return lhs.base() == rhs.base(); }

	template< typename LeftIt, typename RightIt >
		inline bool	operator!=
			(const random_access_iterator<LeftIt>& lhs, const random_access_iterator<RightIt>& rhs)
		{ return lhs.base() != rhs.base(); }

	// Comparison const It & nonconst It operators (random access iterator)
	template< typename LeftIt, typename RightIt >
		inline bool	operator<
			(const random_access_iterator<LeftIt>& lhs, const random_access_iterator<RightIt>& rhs)
		{ return lhs.base() < rhs.base(); }

	template< typename LeftIt, typename RightIt >
		inline bool	operator>
			(const random_access_iterator<LeftIt>& lhs, const random_access_iterator<RightIt>& rhs)
		{ return lhs.base() > rhs.base(); }
	
	template< typename LeftIt, typename RightIt >
		inline bool	operator<=
			(const random_access_iterator<LeftIt>& lhs, const random_access_iterator<RightIt>& rhs)
		{ return lhs.base() <= rhs.base(); }

	template< typename LeftIt, typename RightIt >
		inline bool	operator>=
			(const random_access_iterator<LeftIt>& lhs, const random_access_iterator<RightIt>& rhs)
		{ return lhs.base() >= rhs.base(); }


	// Comparison const It & const It operators (forward iterator)
	template< typename It >
		inline bool	operator==
			(const random_access_iterator<It>& lhs, const random_access_iterator<It>& rhs)
		{ return lhs.base() == rhs.base(); }

	template< typename It >
		inline bool	operator!=
			(const random_access_iterator<It>& lhs, const random_access_iterator<It>& rhs)
		{ return lhs.base() != rhs.base(); }

	// Comparison const It & const It operators (random access iterator)
	template< typename It >
		inline bool	operator<
			(const random_access_iterator<It>& lhs, const random_access_iterator<It>& rhs)
		{ return lhs.base() < rhs.base(); }

	template< typename It >
		inline bool	operator>
			(const random_access_iterator<It>& lhs, const random_access_iterator<It>& rhs)
		{ return lhs.base() > rhs.base(); }

	template< typename It >
		inline bool	operator<=
			(const random_access_iterator<It>& lhs, const random_access_iterator<It>& rhs)
		{ return lhs.base() <= rhs.base(); }

	template< typename It >
		inline bool	operator>=
			(const random_access_iterator<It>& lhs, const random_access_iterator<It>& rhs)
		{ return lhs.base() >= rhs.base(); }

	
} // namespace ft

