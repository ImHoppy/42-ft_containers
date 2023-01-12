#pragma once
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{

	template< typename Iterator >
	class reverse_iterator
	{
		protected:
			typedef iterator_traits<Iterator>	_traits_type;

			Iterator	_current;

		public:
			typedef Iterator									iterator_type;
			typedef typename _traits_type::iterator_category	iterator_category;
			typedef typename _traits_type::value_type			value_type;
			typedef typename _traits_type::difference_type		difference_type;
			typedef typename _traits_type::pointer				pointer;
			typedef typename _traits_type::reference			reference;

			iterator_type	base() const { return _current; };

			reverse_iterator()
				: _current() { }
			
			explicit reverse_iterator(iterator_type it)
				: _current(it) { }

			// Copy constructor
			reverse_iterator(const reverse_iterator& other)
				: _current(other._current) { }

			// Allow conversion from non-const to const iterator
			template<typename Iter>
			reverse_iterator(const reverse_iterator<Iter>& other)
				: _current(other.base()) { }

			// Copy assignment operator
			reverse_iterator &operator=(const reverse_iterator& other)
			{
				if (this == &other)
					return (*this);
				this->_current = other._current;
				return (*this);
			}

			// Forward iterator
			reference	operator*() const { Iterator tmp = _current;  return (*--tmp); }
			pointer		operator->() const { Iterator tmp = _current;  --tmp; return (tmp); }
	
			reverse_iterator&	operator++() { --_current; return *this; }
			reverse_iterator	operator++(int) { reverse_iterator tmp(*this); --_current; return tmp; }

			// Bidirectional iterator
			reverse_iterator&	operator--() { ++_current; return *this; }
			reverse_iterator	operator--(int) { reverse_iterator tmp(*this); ++_current; return tmp; }

			// Random access iterator
			reference	operator[](difference_type n) const { return *(*this + n); }

			reverse_iterator&	operator+=(difference_type n) { _current -= n; return *this; }
			reverse_iterator	operator+(difference_type n) const { return reverse_iterator(_current - n); }

			reverse_iterator&	operator-=(difference_type n) { _current += n; return *this; }
			reverse_iterator	operator-(difference_type n) const { return reverse_iterator(_current + n); }

			// operator reverse_iterator<const T> () const
			// { return (reverse_iterator<const T>(this->_elem)); }

	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}


	template< class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type
    operator-( const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs )
	{
		return (rhs.base() - lhs.base());
	}


	// Comparison const It & nonconst It operators (forward iterator)
	template< typename LeftIt, typename RightIt >
		inline bool	operator==
			(const reverse_iterator<LeftIt>& lhs, const reverse_iterator<RightIt>& rhs)
		{ return lhs.base() == rhs.base(); }

	template< typename LeftIt, typename RightIt >
		inline bool	operator!=
			(const reverse_iterator<LeftIt>& lhs, const reverse_iterator<RightIt>& rhs)
		{ return lhs.base() != rhs.base(); }

	// Comparison const It & nonconst It operators (random access iterator)
	template< typename LeftIt, typename RightIt >
		inline bool	operator<
			(const reverse_iterator<LeftIt>& lhs, const reverse_iterator<RightIt>& rhs)
		{ return lhs.base() > rhs.base(); }

	template< typename LeftIt, typename RightIt >
		inline bool	operator>
			(const reverse_iterator<LeftIt>& lhs, const reverse_iterator<RightIt>& rhs)
		{ return lhs.base() < rhs.base(); }
	
	template< typename LeftIt, typename RightIt >
		inline bool	operator<=
			(const reverse_iterator<LeftIt>& lhs, const reverse_iterator<RightIt>& rhs)
		{ return lhs.base() >= rhs.base(); }

	template< typename LeftIt, typename RightIt >
		inline bool	operator>=
			(const reverse_iterator<LeftIt>& lhs, const reverse_iterator<RightIt>& rhs)
		{ return lhs.base() <= rhs.base(); }


	// Comparison const It & const It operators (forward iterator)
	template< typename It >
		inline bool	operator==
			(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{ return lhs.base() == rhs.base(); }

	template< typename It >
		inline bool	operator!=
			(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{ return lhs.base() != rhs.base(); }

	// Comparison const It & const It operators (random access iterator)
	template< typename It >
		inline bool	operator<
			(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{ return lhs.base() > rhs.base(); }

	template< typename It >
		inline bool	operator>
			(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{ return lhs.base() < rhs.base(); }

	template< typename It >
		inline bool	operator<=
			(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{ return lhs.base() >= rhs.base(); }

	template< typename It >
		inline bool	operator>=
			(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{ return lhs.base() <= rhs.base(); }

	
} // namespace ft

