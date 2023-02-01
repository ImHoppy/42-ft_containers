#pragma once

#include "rb_tree.hpp"
#include "utils.hpp"
#include "set_iterator.hpp"
#include "set_reverse_iterator.hpp"
#include <memory>

namespace ft
{
	template <class T, class Compare = less<T>, class Alloc = std::allocator<pair<const T, T> > >
	class set
	{
	public:
		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		typedef rb_tree<const key_type, value_type, key_compare, allocator_type> tree_type;
		typedef rb_node<const key_type, value_type, key_compare, allocator_type> node_type;

		typedef set_iterator<const key_type, value_type, key_compare> iterator;
		typedef set_iterator<const key_type, value_type, key_compare, true> const_iterator;
		typedef set_reverse_iterator<const key_type, value_type, key_compare> reverse_iterator;
		typedef set_reverse_iterator<const key_type, value_type, key_compare, true> const_reverse_iterator;

	private:
		tree_type _rbTree;
		key_compare _compare;
		allocator_type _alloc;

	public:
		explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _compare(comp), _alloc(alloc) {}

		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _compare(comp), _alloc(alloc)
		{
			insert(first, last);
		}

		set(const set &other)
			: _compare(Compare()), _alloc(allocator_type())
		{
			*this = other;
		}

		~set() { clear(); }

		set &operator=(const set &other)
		{
			if (this != &other)
			{
				clear();
				if (other.size() > 0)
					insert(other.begin(), other.end());
			}
			return *this;
		}

		// Iterators
		iterator begin(void)
		{
			return iterator(_rbTree.treeMinimum(), (_rbTree.size() == 0));
		}
		const_iterator begin(void) const
		{
			return const_iterator(_rbTree.treeMinimum(), (_rbTree.size() == 0));
		}
		iterator end(void)
		{
			return iterator(_rbTree.treeMaximum(), true);
		}
		const_iterator end(void) const
		{
			return const_iterator(_rbTree.treeMaximum(), true);
		}
		reverse_iterator rbegin(void)
		{
			return reverse_iterator(_rbTree.treeMaximum(), (_rbTree.size() == 0));
		}
		const_reverse_iterator rbegin(void) const
		{
			return const_reverse_iterator(_rbTree.treeMaximum(), (_rbTree.size() == 0));
		}
		reverse_iterator rend(void)
		{
			return reverse_iterator(_rbTree.treeMinimum(), true);
		}
		const_reverse_iterator rend(void) const
		{
			return const_reverse_iterator(_rbTree.treeMinimum(), true);
		}
		
		// Capacity
		bool empty(void) const { return _rbTree.size() == 0; }
		size_type size(void) const { return _rbTree.size(); }
		size_type max_size(void) const { return _rbTree.max_size(); }

		// Modifiers
		pair<iterator, bool> insert(const value_type &val)
		{
			bool wasInserted = false;
			iterator inserted = this->_rbTree.insert(pair<const int, int>(val, val), wasInserted);

			return ft::make_pair(iterator(inserted), wasInserted);
		}
		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return insert(val).first;
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			bool useless;
			while (first != last)
			{
				_rbTree.insert(pair<const int, int>(*first, *first), useless);
				++first;
			}
		}
		void erase(iterator position)
		{
			_rbTree.eraseNode(position.getNode());
		}
		size_type erase(const key_type &k)
		{
			return _rbTree.eraseNode(k);
		}
		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				iterator tmp = first;
				++first;
				_rbTree.eraseNode(tmp.getNode());
			}
		}
		void swap(set &other)
		{
			allocator_type tmp_Alloc = _alloc;
			key_compare tmp_Comp = _compare;

			_alloc = other._alloc;
			_compare = other._compare;
			
			other._alloc = tmp_Alloc;
			other._compare = tmp_Comp;
			
			_rbTree.swap(other._rbTree);
		}
		void clear(void)
		{
			_rbTree.clear();
		}

		// Observers
		key_compare key_comp(void) const { return _compare; }
		value_compare value_comp(void) const { return _compare; }

		// Operations
		iterator find(const key_type &k)
		{
			return iterator(_rbTree.find(k));
		}
		size_type count(const key_type &k) const
		{
			return _rbTree.count(k);
		}
		iterator lower_bound(const key_type &k)
		{
			node_type *node = _rbTree.lower_bound(k);
			if (node->isNil())
				return end();
			return iterator(node);
		}
		iterator upper_bound(const key_type &k)
		{
			node_type *node = _rbTree.upper_bound(k);
			if (node->isNil())
				return end();
			return iterator(node);
		}
		const_iterator lower_bound(const key_type &k) const
		{
			node_type *node = _rbTree.lower_bound(k);
			if (node->isNil())
				return end();
			return const_iterator(node);
		}
		const_iterator upper_bound(const key_type &k) const
		{
			node_type *node = _rbTree.upper_bound(k);
			if (node->isNil())
				return end();
			return const_iterator(node);
		}
		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}
		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

		// Allocator
		allocator_type get_allocator(void) const { return _alloc; }
	};

};