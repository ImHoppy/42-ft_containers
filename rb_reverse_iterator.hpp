#pragma once

#include "rb_iterator.hpp"

namespace ft
{

	template <typename T, typename Compare = less<T>, bool IsConst = false>
	class rb_reverse_iterator
	{

	public:
		// Member types
		typedef T value_type;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef rb_iterator<value_type, Compare, IsConst> Iterator;

		typedef typename ft::ternaire<IsConst, value_type *, const value_type *>::type pointer;
		typedef typename ft::ternaire<IsConst, value_type &, const value_type &>::type reference;

	private:
		typedef rb_node<value_type, Compare> node;

	public:
		// Member functions
		rb_reverse_iterator(node *ptr = u_nullptr, bool is_end = false) : _node(ptr), _isEnd(is_end)
		{
			return;
		}
		explicit rb_reverse_iterator(Iterator x) : _node(x.getNode()), _isEnd(x.isEnd())
		{
			++(*this);
			return;
		}
		rb_reverse_iterator(const rb_reverse_iterator<value_type, Compare> &other) : _node(other.getNode()), _isEnd(other.isEnd())
		{
			return;
		}
		~rb_reverse_iterator() { return; }

		rb_reverse_iterator &operator=(const rb_reverse_iterator<value_type, Compare> &other)
		{
			this->_node = other._node;
			this->_isEnd = other._isEnd;
			return *this;
		}

		node *getNode(void) const { return _node; }
		bool isEnd(void) const { return _isEnd; }

		Iterator base(void) const
		{
			rb_reverse_iterator tmp(*this);

			--tmp;
			return Iterator(tmp.getNode(), tmp._isEnd);
		}

		reference operator*(void) const
		{
			return (*this)._node->getValue();
		}
		pointer operator->(void) const
		{
			return &(*this)._node->getValue();
		}

		rb_reverse_iterator &operator++(void)
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
		rb_reverse_iterator &operator--(void)
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
		rb_reverse_iterator operator++(int)
		{
			rb_reverse_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		rb_reverse_iterator operator--(int)
		{
			rb_reverse_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		friend bool operator==(const rb_reverse_iterator &lhs, const rb_reverse_iterator &rhs)
		{
			if (lhs._isEnd != rhs._isEnd)
				return false;
			else if (lhs._isEnd)
				return true;
			else
				return lhs._node == rhs._node;
		}
		friend bool operator!=(const rb_reverse_iterator &lhs, const rb_reverse_iterator &rhs)
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
