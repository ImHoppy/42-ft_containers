#pragma once

#include <iterator>
#include "rb_node.hpp"
#include "utils.hpp"

namespace ft
{

	template <typename T, typename Compare = less<T>, bool IsConst = false>
	class map_iterator
	{

	public:
		// Member types
		typedef T value_type;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		typedef typename ft::ternaire<IsConst, value_type *, const value_type *>::type pointer;
		typedef typename ft::ternaire<IsConst, value_type &, const value_type &>::type reference;

	private:
		typedef rb_node<value_type, Compare> node;

	public:
		// Member functions
		map_iterator(node *ptr = u_nullptr, bool is_end = false) : _node(ptr), _isEnd(is_end)
		{
			return;
		}

		map_iterator(const map_iterator<value_type, Compare> &other) : _node(other.getNode()), _isEnd(other.isEnd())
		{
			return;
		}
		~map_iterator(void) { return; }

		map_iterator &operator=(const map_iterator<value_type, Compare> &other)
		{
			this->_node = other._node;
			this->_isEnd = other._isEnd;
			return *this;
		}

		node *getNode(void) const { return _node; }
		bool isEnd(void) const { return _isEnd; }

		reference operator*(void) const { return this->_node->getValue(); }
		pointer operator->(void) const { return &this->_node->getValue(); }

		map_iterator &operator++(void)
		{
			node *tmp = this->_node->getTreeSuccessor();

			if (tmp->isNil())
				this->_isEnd = true;
			else
				this->_node = tmp;
			return *this;
		}
		map_iterator &operator--(void)
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
		map_iterator operator++(int)
		{
			map_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		map_iterator operator--(int)
		{
			map_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		friend bool operator==(const map_iterator &lhs, const map_iterator &rhs)
		{
			if (lhs._isEnd != rhs._isEnd)
				return false;
			else if (lhs._isEnd)
				return true;
			else
				return lhs._node == rhs._node;
		}
		friend bool operator!=(const map_iterator &lhs, const map_iterator &rhs)
		{
			if (lhs._isEnd != rhs._isEnd)
				return true;
			else if (lhs._isEnd)
				return false;
			else
				return lhs._node != rhs._node;
		}

	private:
		node *_node;
		bool _isEnd;
	};

}
