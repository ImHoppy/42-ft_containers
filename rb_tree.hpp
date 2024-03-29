#pragma once

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "rb_node.hpp"
#include <iostream>
#include <fstream>

namespace ft
{
	template <class T, class Compare = less<T>, class Alloc = std::allocator<T> >
	class rb_tree
	{
	public:
		typedef T value_type;
		typedef Compare key_compare;
		typedef size_t size_type;

		typedef rb_node<value_type, key_compare> node;
		typedef typename Alloc::template rebind<node>::other nodeAlloc;

	private:
		node *_root;
		node *nil;
		size_type _size;
		key_compare _compare;
		nodeAlloc _nodeAlloc;

	public:
		rb_tree(void)
			: _root(u_nullptr), _size(0), _compare()
		{
			_nodeAlloc = nodeAlloc();

			_initNil();
			this->_root = this->nil;
		}
		rb_tree(const key_compare &comp)
			: _root(u_nullptr), _size(0), _compare(comp)
		{
			_nodeAlloc = nodeAlloc();

			_initNil();
			this->_root = this->nil;
		}
		rb_tree(const rb_tree &other)
			: _nodeAlloc(other._nodeAlloc)
		{
			_nodeAlloc = nodeAlloc();
			_initNil();
			*this = other;
		}
		~rb_tree()
		{
			clear();
			_deleteNode(nil);
			nil = u_nullptr;
		}
		rb_tree &operator=(const rb_tree &other)
		{
			if (this != &other)
			{
				_compare = other._compare;
				_size = other._size;
			}
			return *this;
		}
		node *getRoot(void) { return _root; }
		size_type size(void) const { return _size; }
		size_type max_size(void) const { return this->_nodeAlloc.max_size(); }
		void clear(void)
		{
			if (!_root->isNil())
				_clearNodes(_root);
			_root = nil;
		}
		void rotateLeft(node *hinge)
		{
			_rotateSide(hinge, LEFT);
		}
		void rotateRight(node *hinge)
		{
			_rotateSide(hinge, RIGHT);
		}
		node *insert(const value_type &value, bool &wasInserted)
		{
			node *insertionParent = _getInsertionParent(value);
			return insert(insertionParent, value, wasInserted);
		}
		node *insert(node *insertionParent, const value_type &value, bool &wasInserted)
		{
			node *nodeToInsert = nil;
			if (_isEqual(value, insertionParent->getValue()) && !insertionParent->isNil())
			{
				wasInserted = false;
				return insertionParent;
			}
			nodeToInsert = _newNode(value);
			nodeToInsert->parent = insertionParent;
			if (insertionParent->isNil())
				_root = nodeToInsert;
			else if (_compare(nodeToInsert->getValue(), insertionParent->getValue()))
				insertionParent->left = nodeToInsert;
			else
				insertionParent->right = nodeToInsert;
			_insertFixup(nodeToInsert);
			++_size;
			wasInserted = true;
			return nodeToInsert;
		}
		size_type eraseNode(const value_type &key)
		{
			node *nodeToDelete = findNode(key);
			if (nodeToDelete->isNil())
				return 0;
			eraseNode(nodeToDelete);
			return 1;
		}
		size_type eraseNode(node *nodeToDelete)
		{
			node *nodeToFixup = nil;
			node *nodeToReplace = nodeToDelete;
			Color nodeToReplaceOriginalColor = nodeToReplace->color;

			if (nodeToDelete->isNil())
				return 0;
			if (nodeToDelete->left->isNil())
			{
				nodeToFixup = nodeToDelete->right;
				_transplant(nodeToDelete, nodeToDelete->right);
			}
			else if (nodeToDelete->right->isNil())
			{
				nodeToFixup = nodeToDelete->left;
				_transplant(nodeToDelete, nodeToDelete->left);
			}
			else
			{
				nodeToReplace = nodeToDelete->right->getMin();
				nodeToReplaceOriginalColor = nodeToReplace->color;
				nodeToFixup = nodeToReplace->right;
				if (nodeToReplace->parent == nodeToDelete && !nodeToFixup->isNil())
					nodeToFixup->parent = nodeToReplace;
				else
				{
					_transplant(nodeToReplace, nodeToReplace->right);
					nodeToReplace->right = nodeToDelete->right;
					if (!nodeToReplace->right->isNil())
						nodeToReplace->right->parent = nodeToReplace;
				}
				_transplant(nodeToDelete, nodeToReplace);
				nodeToReplace->left = nodeToDelete->left;
				if (!nodeToReplace->left->isNil())
					nodeToReplace->left->parent = nodeToReplace;
				nodeToReplace->color = nodeToDelete->color;
			}
			_deleteNode(nodeToDelete);
			--_size;
			if (nodeToReplaceOriginalColor == BLACK)
				_deleteFixup(nodeToFixup);
			return 1;
		}
		node *findNode(const value_type &key)
		{
			return findNode(_root, key);
		}
		node *findNode(const value_type &key) const
		{
			return findNode(_root, key);
		}
		node *findNode(node *nodeToSearch, const value_type &value)
		{
			if (nodeToSearch->isNil() || _isEqual(nodeToSearch->getValue(), value))
				return nodeToSearch;
			if (_compare(value, nodeToSearch->getValue()))
				return findNode(nodeToSearch->left, value);
			return findNode(nodeToSearch->right, value);
		}
		node *findNode(node *nodeToSearch, const value_type &value) const
		{
			if (nodeToSearch->isNil() || _isEqual(nodeToSearch->getValue(), value))
				return nodeToSearch;
			if (_compare(value, nodeToSearch->getValue()))
				return findNode(nodeToSearch->left, value);
			return findNode(nodeToSearch->right, value);
		}
		node *lower_bound(const value_type &key)
		{
			return lower_bound(_root, key);
		}
		node *lower_bound(const value_type &key) const
		{
			return lower_bound(_root, key);
		}
		node *lower_bound(node *current_node, const value_type &value)
		{
			node *tmp = nil;

			if (current_node->isNil() || _isEqual(value, current_node->getValue()))
				return current_node;
			if (_compare(current_node->getValue(), value))
				return lower_bound(current_node->right, value);
			tmp = lower_bound(current_node->left, value);
			if (tmp->isNil())
				return current_node;
			return tmp;
		}
		node *lower_bound(node *current_node, const value_type &value) const
		{
			node *tmp = nil;

			if (current_node->isNil() || _isEqual(value, current_node->getValue()))
				return current_node;
			if (_compare(current_node->getValue(), value))
				return lower_bound(current_node->right, value);
			tmp = lower_bound(current_node->left, value);
			if (tmp->isNil())
				return current_node;
			return tmp;
		}
		node *upper_bound(const value_type &value)
		{
			return upper_bound(_root, value);
		}
		node *upper_bound(const value_type &value) const
		{
			return upper_bound(_root, value);
		}
		node *upper_bound(node *current_node, const value_type &value)
		{
			node *tmp = nil;

			if (current_node->isNil())
				return current_node;
			if (_compare(current_node->getValue(), value) || _isEqual(current_node->getValue(), value))
				return upper_bound(current_node->right, value);
			tmp = upper_bound(current_node->left, value);
			if (tmp->isNil())
				return current_node;
			return tmp;
		}
		node *upper_bound(node *current_node, const value_type &value) const
		{
			node *tmp = nil;

			if (current_node->isNil())
				return current_node;
			if (_compare(current_node->getValue(), value) || _isEqual(current_node->getValue(), value))
				return upper_bound(current_node->right, value);
			tmp = upper_bound(current_node->left, value);
			if (tmp->isNil())
				return current_node;
			return tmp;
		}
		node *treeMinimum(void)
		{
			return _root->getMin();
		}
		node *treeMinimum(void) const
		{
			return _root->getMin();
		}
		node *treeMaximum(void)
		{
			return _root->getMax();
		}
		node *treeMaximum(void) const
		{
			return _root->getMax();
		}
		void swap(rb_tree &other)
		{
			node *tmp_root = other._root;
			node *tmp_nil = other.nil;
			size_type tmp_size = other._size;
			key_compare tmp_compare = other._compare;
			nodeAlloc tmp_nodeAlloc = other._nodeAlloc;

			other._root = this->_root;
			other.nil = this->nil;
			other._size = this->_size;
			other._compare = this->_compare;
			other._nodeAlloc = this->_nodeAlloc;

			this->_root = tmp_root;
			this->nil = tmp_nil;
			this->_size = tmp_size;
			this->_compare = tmp_compare;
			this->_nodeAlloc = tmp_nodeAlloc;
		}

	private:
		void _initNil(void)
		{
			// Init nil node
			value_type nilValue = value_type();

			nil = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(nil, node(nilValue));
			nil->color = BLACK;
			nil->parent = nil;
			nil->left = nil;
			nil->right = nil;
		}

		node *_newNode(const value_type &value)
		{
			node *new_node = _nodeAlloc.allocate(1);

			_nodeAlloc.construct(new_node, node(value));
			new_node->left = nil;
			new_node->right = nil;
			new_node->parent = nil;
			new_node->color = RED;
			return new_node;
		}
		void _deleteNode(node *node)
		{
			_nodeAlloc.destroy(node);
			_nodeAlloc.deallocate(node, 1);
		}
		void _transplant(node *oldNode, node *newNode)
		{
			if (oldNode->parent->isNil())
				_root = newNode;
			else if (oldNode->isALeftChild())
				oldNode->parent->left = newNode;
			else
				oldNode->parent->right = newNode;
			if (!newNode->isNil())
				newNode->parent = oldNode->parent;
		}
		void _deleteFixup(node *fixNode)
		{
			node *save = nil;

			while (fixNode != _root && fixNode->color == BLACK)
			{
				if (fixNode == fixNode->parent->left)
				{
					save = fixNode->parent->right;
					if (save->color == RED)
					{
						save->color = BLACK;
						fixNode->parent->color = RED;
						rotateLeft(fixNode->parent);
						save = fixNode->parent->right;
					}
					if (save->left->color == BLACK && save->right->color == BLACK)
					{
						save->color = RED;
						fixNode = fixNode->parent;
					}
					else
					{
						if (save->right->color == BLACK)
						{
							save->left->color = BLACK;
							save->color = RED;
							rotateRight(save);
							save = fixNode->parent->right;
						}
						save->color = fixNode->parent->color;
						fixNode->parent->color = BLACK;
						save->right->color = BLACK;
						rotateLeft(fixNode->parent);
						fixNode = _root;
					}
				}
				else
				{
					save = fixNode->parent->left;
					if (save->color == RED)
					{
						save->color = BLACK;
						fixNode->parent->color = RED;
						rotateRight(fixNode->parent);
						save = fixNode->parent->left;
					}
					if (save->right->color == BLACK && save->left->color == BLACK)
					{
						save->color = RED;
						fixNode = fixNode->parent;
					}
					else
					{
						if (save->left->color == BLACK)
						{
							save->right->color = BLACK;
							save->color = RED;
							rotateLeft(save);
							save = fixNode->parent->left;
						}
						save->color = fixNode->parent->color;
						fixNode->parent->color = BLACK;
						save->left->color = BLACK;
						rotateRight(fixNode->parent);
						fixNode = _root;
					}
				}
			}
			fixNode->color = BLACK;
		}
		void _clearNodes(node *nodeToDelete)
		{
			if (!nodeToDelete->left->isNil())
				_clearNodes(nodeToDelete->left);
			if (!nodeToDelete->right->isNil())
				_clearNodes(nodeToDelete->right);
			_deleteNode(nodeToDelete);
			--_size;
		}
		void _rotateSide(node *hinge, Side side)
		{
			node *movedNode = hinge->getChild(side == LEFT ? RIGHT : LEFT);
			if (side == LEFT)
				hinge->right = movedNode->left;
			else
				hinge->left = movedNode->right;
			if (!movedNode->getChild(side)->isNil())
				movedNode->getChild(side)->parent = hinge;
			if (!movedNode->isNil())
				movedNode->parent = hinge->parent;
			if (hinge->parent->isNil())
				_root = movedNode;
			else if (hinge->isALeftChild())
				hinge->parent->left = movedNode;
			else
				hinge->parent->right = movedNode;
			if (side == LEFT)
				movedNode->left = hinge;
			else
				movedNode->right = hinge;
			if (!hinge->isNil())
				hinge->parent = movedNode;
		}
		node *_getInsertionParent(const value_type &insertValue)
		{
			node *traversingTree = _root;
			node *result = nil;

			while (!traversingTree->isNil())
			{
				result = traversingTree;
				if (_compare(insertValue, traversingTree->getValue()))
					traversingTree = traversingTree->left;
				else if (_isEqual(insertValue, traversingTree->getValue()))
					return result;
				else
					traversingTree = traversingTree->right;
			}
			return result;
		}
		void _insertFixup(node *lastInsertedNode)
		{
			node *tmp;

			while (lastInsertedNode->parent->color == RED)
			{
				if (lastInsertedNode->parent == lastInsertedNode->parent->parent->left)
				{
					tmp = lastInsertedNode->parent->parent->right;
					if (tmp->color == RED)
					{
						tmp->color = BLACK;
						lastInsertedNode->parent->color = BLACK;
						lastInsertedNode->parent->parent->color = RED;
						lastInsertedNode = lastInsertedNode->parent->parent;
					}
					else
					{
						if (lastInsertedNode == lastInsertedNode->parent->right)
						{
							lastInsertedNode = lastInsertedNode->parent;
							rotateLeft(lastInsertedNode);
						}
						lastInsertedNode->parent->color = BLACK;
						lastInsertedNode->parent->parent->color = RED;
						rotateRight(lastInsertedNode->parent->parent);
					}
				}
				else
				{
					tmp = lastInsertedNode->parent->parent->left;
					if (tmp->color == RED)
					{
						lastInsertedNode->parent->color = BLACK;
						tmp->color = BLACK;
						lastInsertedNode->parent->parent->color = RED;
						lastInsertedNode = lastInsertedNode->parent->parent;
					}
					else
					{
						if (lastInsertedNode == lastInsertedNode->parent->left)
						{
							lastInsertedNode = lastInsertedNode->parent;
							rotateRight(lastInsertedNode);
						}
						lastInsertedNode->parent->color = BLACK;
						lastInsertedNode->parent->parent->color = RED;
						rotateLeft(lastInsertedNode->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		}
		bool _isEqual(const value_type &key1, const value_type &key2) const
		{
			return !_compare(key1, key2) && !_compare(key2, key1);
		}
	};
}