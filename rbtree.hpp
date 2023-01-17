#pragma once

#include "utils.hpp"
#include <memory>

namespace ft
{
	enum rb_color { RED = true, BLACK = false }; 

	template <class T>
	class rb_iterator
	{
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		typedef rb_iterator<T> self;
		typedef rb_node<T> node;
		typedef typename rb_node::ptr node_ptr;


		rb_iterator() : _node(NULL) {}
		rb_iterator(node_ptr node) : _node(node) {}
		rb_iterator(const self &other) : _node(other._node) {}
		~rb_iterator() {}

		reference operator*() const { return _node->key; }
		pointer operator->() const { return &(_node->key); }
		
		self& operator++()
		{
			_node = _node->successor();
			return *this;
		}
		self operator++(int)
		{
			self tmp = *this;
			_node = _node->successor();
			return tmp;
		}
		self &operator--()
		{
			_node = _node->predecessor();
			return *this;
		}
		self operator--(int)
		{
			self tmp = *this;
			_node = _node->predecessor();
			return tmp;
		}

		friend bool operator==(const self &lhs, const self &rhs) { return lhs._node == rhs._node; }
		friend bool operator!=(const self &lhs, const self &rhs) { return lhs._node != rhs._node; }
	private:
		node_ptr _node;
	};

	template <class T, class Alloc = std::allocator<T> >
	struct rb_node1
	{
		typedef rb_node *ptr;
		typedef const rb_node *const_ptr;

		T key;
		ptr *parent;
		ptr *left;
		ptr *right;
		bool color;
		bool is_nil;
		Alloc allocator;

		rb_node() : parent(NULL), left(NULL), right(NULL), color(BLACK), is_nil(true) {}

		rb_node(const T &key, rb_node *parent, rb_node *left, rb_node *right, bool color, bool is_nil)
			: key(key), parent(parent), left(left), right(right), color(color), is_nil(is_nil) {}

		rb_node(const rb_node &other)
			: key(other.key), parent(other.parent), left(other.left), right(other.right), color(other.color), is_nil(other.is_nil) {}

		rb_node &operator=(const rb_node &other)
		{
			if (this != &other)
			{
				key = other.key;
				parent = other.parent;
				left = other.left;
				right = other.right;
				color = other.color;
				is_nil = other.is_nil;
			}
			return *this;
		}

		~rb_node() {}

		static ptr minium()
		{
			ptr node = this;
			while (!node->left->is_nil)
				node = node->left;
			return node;
		}
		static ptr minium(ptr x)
		{
			while (!x->left->is_nil)
				x = x->left;
			return x;
		}
		static ptr minium(const_ptr x)
		{
			while (!x->left->is_nil)
				x = x->left;
			return x;
		}
		static ptr maximum()
		{
			ptr node = this;
			while (!node->right->is_nil)
				node = node->right;
			return node;
		}
		static ptr maximum(ptr x)
		{
			while (!x->right->is_nil)
				x = x->right;
			return x;
		}
		static ptr maximum(const_ptr x)
		{
			while (!x->right->is_nil)
				x = x->right;
			return x;
		}

		ptr successor()
		{
			if (!right->is_nil)
				return minium(right);
			ptr y = parent;
			while (y != NULL && this == y->right)
			{
				this = y;
				y = y->parent;
			}
			return y;
		}
		ptr predecessor()
		{
			if (!left->is_nil)
				return maximum(left);
			ptr y = parent;
			while (y != NULL && this == y->left)
			{
				this = y;
				y = y->parent;
			}
			return y;
		}

		static ptr successor(ptr x)
		{
			if (!x->right->is_nil)
				return minium(x->right);
			ptr y = x->parent;
			while (y != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		static ptr successor(const_ptr x)
		{
			if (!x->right->is_nil)
				return minium(x->right);
			ptr y = x->parent;
			while (y != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		static ptr predecessor(ptr x)
		{
			if (!x->left->is_nil)
				return maximum(x->left);
			ptr y = x->parent;
			while (y != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		static ptr predecessor(const_ptr x)
		{
			if (!x->left->is_nil)
				return maximum(x->left);
			ptr y = x->parent;
			while (y != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		void clear()
		{
			if (!left->is_nil)
				left->clear();
			if (!right->is_nil)
				right->clear();
			allocator.destroy(this);
		}
	};

	template <class T, class Compare, class Alloc = std::allocator<T> >
	class rb_tree1
	{
	public:
		typedef rb_iterator iterator;
		typedef rb_iterator const_iterator;
		typedef rb_iterator reverse_iterator;
		typedef rb_iterator const_reverse_iterator;
		typedef T value_type;
		typedef Compare key_compare;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;

		typedef rb_tree<T, Compare, Alloc> self;
		typedef rb_node<T> node;
		typedef typename node::ptr node_ptr;
		typedef Alloc allocator_type;
		

	private:
		node_ptr root;
		node_ptr nil;
		allocator_type allocator;
	public:
		rb_tree() : root(NULL), nil(NULL) {}
		rb_tree(const self &other)
		{
			*this = other;
		}
		~rb_tree()
		{
			clear();
		}

		self &operator=(const self &other)
		{
			if (this != &other)
			{
				clear();
				root = copy(other.root);
				nil = root->parent;
			}
			return *this;
		}
		
		iterator begin() { return iterator(root->left); }
		const_iterator begin() const { return const_iterator(root->left); }
		iterator end() { return iterator(nil); }
		const_iterator end() const { return const_iterator(nil); }
		reverse_iterator rbegin() { return reverse_iterator(nil->predecessor()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(nil->predecessor()); }
		reverse_iterator rend() { return reverse_iterator(root); }
		const_reverse_iterator rend() const { return const_reverse_iterator(root); }

		bool empty() const { return root->left->is_nil; }
		size_type size() const { return size(root->left); }
		size_type max_size() const { return size_type(-1); }

		void clear()
		{
			clear(root->left);
			root->left = nil;
		}

		iterator insert(const value_type &val)
		{
			node_ptr y = root;
			node_ptr x = root->left;
			while (!x->is_nil)
			{
				y = x;
				if (key_compare()(val, x->key))
					x = x->left;
				else
					x = x->right;
			}
			node_ptr z = allocator.allocate(sizeof(node), node(val, y, nil, nil, RED, false));
			if (y->is_nil)
				root->left = z;
			else if (key_compare()(z->key, y->key))
				y->left = z;
			else
				y->right = z;
			insert_fixup(z);
			return iterator(z);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void erase(iterator position)
		{
			node_ptr z = position.node;
			node_ptr y = z;
			node_ptr x;
			color y_original_color = y->color;
			if (z->left->is_nil)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right->is_nil)
			{
				x = z->left;
				transplant(z, z->left);
			}
			else
			{
				y = z->right->minium();
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (y_original_color == BLACK)
				erase_fixup(x);
			allocator.destroy(z);
		}
		size_type erase(const key_type &k)
		{
			iterator it = find(k);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}
		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				iterator tmp = first;
				++first;
				erase(tmp);
			}
		}

		iterator find(const key_type &k)
		{
			node_ptr x = root->left;
			while (!x->is_nil)
			{
				if (key_compare()(k, x->key))
					x = x->left;
				else if (key_compare()(x->key, k))
					x = x->right;
				else
					return iterator(x);
			}
			return end();
		}
		const_iterator find(const key_type &k) const
		{
			node_ptr x = root->left;
			while (!x->is_nil)
			{
				if (key_compare()(k, x->key))
					x = x->left;
				else if (key_compare()(x->key, k))
					x = x->right;
				else
					return const_iterator(x);
			}
			return end();
		}

		size_type count(const key_type &k) const
		{
			return find(k) == end() ? 0 : 1;
		}

		iterator lower_bound(const key_type &k)
		{
			node_ptr x = root->left;
			node_ptr y = nil;
			while (!x->is_nil)
			{
				if (key_compare()(x->key, k))
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return iterator(y);
		}

		const_iterator lower_bound(const key_type &k) const
		{
			node_ptr x = root->left;
			node_ptr y = nil;
			while (!x->is_nil)
			{
				if (key_compare()(x->key, k))
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return const_iterator(y);
		}
		

	};
	
	template <class T>
	struct rb_node
	{
		T key;
		node *left;
		node *right;
		node *parent;
		color color;
	};
	
	template <class T, class Compare, class Alloc = std::allocator<T> >
	class rb_tree
	{
		public:
		typedef rb_node node;
		typedef node *node_ptr;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;

		private:
		node_ptr root;
		node_ptr nil;
		key_compare key_compare;
		allocator_type allocator;
		size_type node_count;

		void _insert_fixup(node_ptr node)
		{
			node_ptr u;
			while (node->parent->color == RED)
			{
				if (node->parent == node->parent->parent->right)
				{
					u = node->parent->parent->left;
					if (u->color == RED)
					{
						node->parent->color = BLACK;
						u->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							right_rotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						left_rotate(node->parent->parent);
					}
				}
				else
				{
					u = node->parent->parent->right;
					if (u->color == RED)
					{
						node->parent->color = BLACK;
						u->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							left_rotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						right_rotate(node->parent->parent);
					}
				}
				if (node == root)
					break;
			}
			root->color = BLACK;
		}

		void _erase(node_ptr node, value_type key)
		{
			node_ptr z = nil;
			node_ptr x;
			node_ptr y;
			while (!node != nil)
			{
				if (node->key == key)
				{
					z = node;
				}
				else if (key_compare()(node->key, key))
					node = node->left;
				else
					node = node->right;
			}
			if (z == nil)
				return;
			y = z;
			color y_original_color = y->color;
			if (z->left == nil)
			{
				x = z->right;
				_transplant(z, z->right);
			}
			else if (z->right == nil)
			{
				x = z->left;
				_transplant(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			allocator.destroy(z);
			if (y_original_color == BLACK)
				_erase_fixup(x);
		}

		public:
		rb_tree() :
			root(NULL), nil(NULL), key_compare(), allocator(), node_count(0)
		{
			nil = allocator.allocate(1);
			nil->left = nil;
			nil->right = nil;
			nil->parent = nil;
			nil->color = BLACK;
			root = nil;
		}

		node_ptr minimum(node_ptr x)
		{
			while (x->left != nil)
				x = x->left;
			return x;
		}
		node_ptr maximum(node_ptr x)
		{
			while (x->right != nil)
				x = x->right;
			return x;
		}
		node_ptr successor(node_ptr x)
		{
			if (x->right != nil)
				return minimum(x->right);
			node_ptr y = x->parent;
			while (y != nil && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		node_ptr predecessor(node_ptr x)
		{
			if (x->left != nil)
				return maximum(x->left);
			node_ptr y = x->parent;
			while (y != nil && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		void left_rotate(node_ptr x)
		{
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == nil)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		void right_rotate(node_ptr x)
		{
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == nil)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		void insert(T key)
		{
			node_ptr node = allocator.allocate(1);
			node->parent = nil;
			node->key = key;
			node->left = nil;
			node->right = nil;
			node->color = RED;

			node_ptr x = this->root;
			node_ptr y = nil;
			while (x != nil)
			{
				y = x;
				if (key_compare()(node->key, x->key))
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == nil)
				root = node;
			else if (key_compare()(node->key, y->key))
				y->left = node;
			else
				y->right = node;
			
			if (node->parent == nil)
			{
				node->color = BLACK;
				return;
			}
			if (node->parent->parent == nil)
				return;
			_insert_fixup(node);
		}

		void erase(value_type key)
		{
			_erase(root, key);
		}

		node_ptr getRoot()
		{
			return root;
		}
		 
	};
} // namespace ft
