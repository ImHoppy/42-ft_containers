#pragma once

#include "map_iterator.hpp"

namespace ft
{

template < typename Key, typename T, typename Compare = std::less<const Key>,
		 bool IsConst = false >
class map_reverse_iterator
{

public:

	// Member types
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;
	typedef	map_iterator<const Key, T, Compare, IsConst>		Iterator;

	typedef	const Key			key_type;
	typedef	T					mapped_type;
	typedef	pair<const Key, T>	value_type;
	typedef typename ft::ternaire<IsConst, value_type*, const value_type*>::type	pointer;
	typedef typename ft::ternaire<IsConst, value_type&, const value_type&>::type	reference;

private:

	typedef rb_node<Key, T, Compare>			node;

public:

	// Member functions
	map_reverse_iterator( node *ptr = NULL, bool is_end = false ) :
		_node(ptr), _isEnd(is_end)
	{
		return;
	}
	explicit map_reverse_iterator( Iterator x ):
		_node(x.getNode()), _isEnd(x.isEnd())
	{
		++(*this);
		return;
	}
	map_reverse_iterator( const map_reverse_iterator<const Key, T, Compare> &other ):
		_node(other.getNode()), _isEnd(other.isEnd())
	{
		return;
	}
	~map_reverse_iterator( void ) { return; }

	map_reverse_iterator &operator=( const map_reverse_iterator<const Key, T, Compare> &other )
	{
		this->_node = other._node;
		this->_isEnd = other._isEnd;
		return *this;
	}

	node	*getNode( void ) const { return _node; }
	bool	isEnd( void ) const { return _isEnd; }

	Iterator	base( void ) const
	{
		map_reverse_iterator	tmp(*this);

		--tmp;
		return Iterator(tmp.getNode(), tmp._isEnd);
	}

	reference			operator*( void ) const
	{
		return (*this)._node->getValue();
	}
	pointer				operator->( void ) const
	{
		return &(*this)._node->getValue();
	}

	map_reverse_iterator&	operator++( void )
	{
		node *tmp = this->_node->getTreePredecessor();
		
		if (this->_isEnd == true)
			this->_isEnd = false;
		else if (tmp->isNil())
			this->_isEnd = true;
		else
			this->_node = tmp;
		return *this;
	}  
	map_reverse_iterator&	operator--( void )
	{
		node *tmp = this->_node->getTreeSuccessor();
		
		if (this->_isEnd)
			this->_isEnd = false;
		else if (tmp->isNil())
			this->_isEnd = true;
		else
			this->_node = tmp;
		return *this;

	}
	map_reverse_iterator		operator++( int ) {
		map_reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	map_reverse_iterator		operator--( int ) {
		map_reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const map_reverse_iterator& lhs, const map_reverse_iterator& rhs )
	{
		if (lhs._isEnd != rhs._isEnd)
			return false;
		else if (lhs._isEnd)
			return true;
		else
			return lhs._node == rhs._node;
	}
	friend bool	operator!=( const map_reverse_iterator& lhs, const map_reverse_iterator& rhs )
	{
		if (lhs._isEnd != rhs._isEnd)
			return true;
		else if (lhs._isEnd)
			return false;
		else
			return lhs._node != rhs._node;
	}

private:

	node	*_node;
	bool	_isEnd;

};

}
