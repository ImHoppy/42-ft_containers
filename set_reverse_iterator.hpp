#pragma once

#include "set_iterator.hpp"

namespace ft
{

template < typename Key, typename T, typename Compare = less<const Key>,
		 bool IsConst = false >
class set_reverse_iterator
{

public:

	// Member types
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t					difference_type;
	typedef size_t						size_type;
	typedef	set_iterator<const Key, T, Compare, IsConst>		Iterator;

	typedef	const Key			key_type;
	typedef	T					mapped_type;
	typedef	pair<const Key, T>	value_type;
	typedef typename ft::ternaire<IsConst, value_type*, const value_type*>::type	pointer;
	typedef typename ft::ternaire<IsConst, value_type&, const value_type&>::type	reference;

private:

	typedef rb_node<Key, T, Compare>			node;

public:

	// Member functions
	set_reverse_iterator( node *ptr = u_nullptr, bool is_end = false ) :
		_node(ptr), _isEnd(is_end)
	{
		return;
	}
	explicit set_reverse_iterator( Iterator x ):
		_node(x.getNode()), _isEnd(x.isEnd())
	{
		++(*this);
		return;
	}
	set_reverse_iterator( const set_reverse_iterator<const Key, T, Compare> &other ):
		_node(other.getNode()), _isEnd(other.isEnd())
	{
		return;
	}
	~set_reverse_iterator( void ) { return; }

	set_reverse_iterator &operator=( const set_reverse_iterator<const Key, T, Compare> &other )
	{
		this->_node = other._node;
		this->_isEnd = other._isEnd;
		return *this;
	}

	node	*getNode( void ) const { return _node; }
	bool	isEnd( void ) const { return _isEnd; }

	Iterator	base( void ) const
	{
		set_reverse_iterator	tmp(*this);

		--tmp;
		return Iterator(tmp.getNode(), tmp._isEnd);
	}

	reference			operator*( void ) const
	{
		return (*this)._node->getValue().first;
	}
	pointer				operator->( void ) const
	{
		return &(*this)._node->getValue().first;
	}

	set_reverse_iterator&	operator++( void )
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
	set_reverse_iterator&	operator--( void )
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
	set_reverse_iterator		operator++( int ) {
		set_reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	set_reverse_iterator		operator--( int ) {
		set_reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const set_reverse_iterator& lhs, const set_reverse_iterator& rhs )
	{
		if (lhs._isEnd != rhs._isEnd)
			return false;
		else if (lhs._isEnd)
			return true;
		else
			return lhs._node == rhs._node;
	}
	friend bool	operator!=( const set_reverse_iterator& lhs, const set_reverse_iterator& rhs )
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
