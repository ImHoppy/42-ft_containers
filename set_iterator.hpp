#pragma once

#include <iterator>
#include "rb_node.hpp"
#include "utils.hpp"

namespace ft
{

template < typename Key, typename T, typename Compare = less<Key>,
		 bool IsConst = false >
class set_iterator
{

public:

	// Member types
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t					difference_type;
	typedef size_t						size_type;

	typedef	const Key			key_type;
	typedef	T					mapped_type;
	typedef	pair<const Key, T>	value_type;
	typedef typename ft::ternaire<IsConst, T*, const T*>::type	pointer;
	typedef typename ft::ternaire<IsConst, T&, const T&>::type	reference;

private:

	typedef rb_node<Key, T, Compare>			node;

public:

	// Member functions
	set_iterator( node *ptr = u_nullptr, bool is_end = false ) :
		_node(ptr), _isEnd(is_end)
	{
		return;
	}

	set_iterator( const set_iterator<const Key, T, Compare> &other ):
		_node(other.getNode()), _isEnd(other.isEnd())
	{
		return;
	}
	~set_iterator( void ) { return; }

	set_iterator &operator=( const set_iterator<const Key, T, Compare> &other )
	{
		this->_node = other._node;
		this->_isEnd = other._isEnd;
		return *this;
	}

	node	*getNode( void ) const { return _node; }
	bool	isEnd( void ) const { return _isEnd; }

	reference			operator*( void ) const { return this->_node->getValue().second; }
	pointer				operator->( void ) const { return &this->_node->getValue().second; }

	set_iterator&	operator++( void )
	{
		node *tmp = this->_node->getTreeSuccessor();
		
		if (tmp->isNil())
			this->_isEnd = true;
		else
			this->_node = tmp;
		return *this;
	}  
	set_iterator&	operator--( void )
	{
		node *tmp = this->_node->getTreePredecessor();
		
		if (this->_isEnd)
			this->_isEnd = false;
		else if (tmp->isNil())
			this->_isEnd = true;
		else
			this->_node = tmp;
		return *this;

	}  
	set_iterator		operator++( int ) {
		set_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	set_iterator		operator--( int ) {
		set_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const set_iterator& lhs, const set_iterator& rhs )
	{
		if (lhs._isEnd != rhs._isEnd)
			return false;
		else if (lhs._isEnd)
			return true;
		else
			return lhs._node == rhs._node;
	}
	friend bool	operator!=( const set_iterator& lhs, const set_iterator& rhs )
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
