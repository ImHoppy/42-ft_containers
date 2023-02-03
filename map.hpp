#pragma once

#include "rb_tree.hpp"
#include "rb_iterator.hpp"
#include "rb_reverse_iterator.hpp"
#include "type_traits.hpp"

namespace ft
{

	template <typename Key, typename T, typename Compare = less<Key>,
			  typename Alloc = std::allocator<pair<const Key, T> > >
	class map
	{

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		class value_compare : public binary_function<value_type, value_type, bool>
		{
			friend class map;

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

		protected:
			key_compare comp;

			value_compare(key_compare c) : comp(c)
			{
				return;
			}

		public:
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	public:
		typedef rb_iterator<value_type, value_compare> iterator;
		typedef rb_iterator<value_type, value_compare, true> const_iterator;
		typedef ft::rb_reverse_iterator<value_type, value_compare> reverse_iterator;
		typedef ft::rb_reverse_iterator<value_type, value_compare, true> const_reverse_iterator;

	private:
		typedef rb_tree<value_type, value_compare, allocator_type> tree_type;
		typedef rb_node<value_type, value_compare> node_type;

	public:
		explicit map(const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type())
			: _rbTree(value_compare(cmp)), _compare(cmp), _alloc(alloc)
		{
			return;
		}
		template <typename InputIt>
		map(InputIt first, InputIt last, const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type())
			: _rbTree(value_compare(cmp)), _compare(cmp), _alloc(alloc)
		{
			this->insert(first, last);
		}
		map(const map &other)
			: _rbTree(value_compare(other._compare)), _compare(other._compare), _alloc(other._alloc)
		{
			*this = other;
		}
		~map()
		{
			clear();
		}

		map &operator=(const map &other)
		{
			if (this != &other)
			{
				clear();
				if (other.size() > 0)
					this->insert(other.begin(), other.end());
			}
			return *this;
		}

		mapped_type &operator[](const key_type &key)
		{
			return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;
		}
		mapped_type &at(const key_type &key)
		{
			if (_alreadyExists(key))
				throw std::out_of_range("map::at");
			else
				return (*this)[key];
		}
		const mapped_type &at(const key_type &key) const
		{
			if (_alreadyExists(key))
				throw std::out_of_range("map::at");
			else
				return (*this)[key];
		}

		iterator begin(void)
		{
			return iterator(this->_rbTree.treeMinimum(), (_rbTree.size() == 0));
		}
		const_iterator begin(void) const
		{
			return const_iterator(this->_rbTree.treeMinimum(), (_rbTree.size() == 0));
		}
		iterator end(void)
		{
			return iterator(this->_rbTree.treeMaximum(), true);
		}
		const_iterator end(void) const
		{
			return const_iterator(this->_rbTree.treeMaximum(), true);
		}
		reverse_iterator rbegin(void)
		{
			return reverse_iterator(this->_rbTree.treeMaximum(), (_rbTree.size() == 0));
		}
		const_reverse_iterator rbegin(void) const
		{
			return const_reverse_iterator(this->_rbTree.treeMaximum(), (_rbTree.size() == 0));
		}
		reverse_iterator rend(void)
		{
			return reverse_iterator(this->_rbTree.treeMinimum(), true);
		}
		const_reverse_iterator rend(void) const
		{
			return const_reverse_iterator(this->_rbTree.treeMinimum(), true);
		}

		bool empty(void) const { return _rbTree.size() == 0; }
		size_type size(void) const { return _rbTree.size(); }
		size_type max_size(void) const { return _rbTree.max_size(); }

		key_compare key_comp(void) const { return this->_compare; }
		value_compare value_comp() const
		{
			return value_compare(key_comp());
		}
		allocator_type get_allocator(void) const { return this->_alloc; }

		iterator find(const key_type &key)
		{
			node_type *result = _rbTree.findNode(value_type(key, mapped_type()));

			if (result->isNil())
				return this->end();
			return iterator(result);
		}
		const_iterator find(const key_type &key) const
		{
			node_type *result = _rbTree.findNode(value_type(key, mapped_type()));

			if (result->isNil())
				return this->end();
			return const_iterator(result);
		}
		size_type count(const key_type &key) const
		{
			if (_rbTree.findNode(value_type(key, mapped_type()))->isNil())
				return 0;
			return 1;
		}
		iterator lower_bound(const key_type &key)
		{
			node_type *result = _rbTree.lower_bound(value_type(key, mapped_type()));

			if (result->isNil())
				return this->end();
			return iterator(result);
		}
		const_iterator lower_bound(const key_type &key) const
		{
			node_type *result = _rbTree.lower_bound(value_type(key, mapped_type()));

			if (result->isNil())
				return this->end();
			return const_iterator(result);
		}
		iterator upper_bound(const key_type &key)
		{
			node_type *result = _rbTree.upper_bound(value_type(key, mapped_type()));

			if (result->isNil())
				return this->end();
			return iterator(result);
		}
		const_iterator upper_bound(const key_type &key) const
		{
			node_type *result = _rbTree.upper_bound(value_type(key, mapped_type()));

			if (result->isNil())
				return this->end();
			return const_iterator(result);
		}
		ft::pair<iterator, iterator> equal_range(const key_type &key)
		{
			return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
		}

		ft::pair<iterator, bool> insert(const value_type &value)
		{
			bool wasInserted = false;
			node_type *inserted = this->_rbTree.insert(value, wasInserted);

			return ft::make_pair(iterator(inserted), wasInserted);
		}
		iterator insert(iterator position, const value_type &value)
		{
			bool placeholder = false;
			(void)position;
			return this->_rbTree.insert(value, placeholder);
		}
		template <typename InputIt>
		void insert(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0)
		{
			bool useless;

			while (first != last)
			{
				this->_rbTree.insert(*first, useless);
				first++;
			}
		}

		void erase(iterator position)
		{
			this->_rbTree.eraseNode(position.getNode());
		}
		void erase(iterator first, iterator last)
		{
			while (first != last)
				this->_rbTree.eraseNode((first++).getNode());
		}
		size_type erase(const key_type &key)
		{
			return this->_rbTree.eraseNode(value_type(key, mapped_type()));
		}

		void clear(void)
		{
			this->_rbTree.clear();
		}

		void swap(map &other)
		{
			allocator_type tmp_valueAlloc = other._alloc;
			key_compare tmp_comparator = other._compare;

			other._alloc = this->_alloc;
			other._compare = this->_compare;
			this->_alloc = tmp_valueAlloc;
			this->_compare = tmp_comparator;
			this->_rbTree.swap(other._rbTree);
		}

		friend bool operator==(const map &lhs, const map &rhs)
		{
			const_iterator lhs_it = lhs.begin();
			const_iterator lhs_ite = lhs.end();
			const_iterator rhs_it = rhs.begin();
			const_iterator rhs_ite = rhs.end();

			while (lhs_it != lhs_ite && rhs_it != rhs_ite)
			{
				if (lhs_it->second != rhs_it->second)
					return false;
				lhs_it++;
				rhs_it++;
			}
			if (lhs_it != lhs_ite || rhs_it != rhs_ite)
				return false;
			return true;
		}
		friend bool operator!=(const map &lhs, const map &rhs)
		{
			return !(lhs == rhs);
		}
		friend bool operator<(const map &lhs, const map &rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		friend bool operator>(const map &lhs, const map &rhs)
		{
			return rhs < lhs;
		}
		friend bool operator<=(const map &lhs, const map &rhs)
		{
			return !(rhs < lhs);
		}
		friend bool operator>=(const map &lhs, const map &rhs)
		{
			return !(lhs < rhs);
		}
		friend void swap(map &rhs, map &lhs)
		{
			lhs.swap(rhs);
		}

		// void printTree(std::string file = "tree_visualisation.mmd") const
		// {
		// 	_rbTree.printTree(file);
		// }

	private:
		tree_type _rbTree;
		key_compare _compare;
		allocator_type _alloc;

		bool _alreadyExists(const key_type &key) const
		{
			return _rbTree.findNode(value_type(key, mapped_type()))->isNil();
		}
	};

}
