#pragma once

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "rb_node.hpp"
#include <iostream>
#include <fstream>

namespace ft
{
	template <class Key, class T, class Compare = less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class rb_tree
	{
	public:
		typedef rb_node<const Key, T, Compare, Allocator> node;
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef size_t size_type;

		rb_tree(void) : _root(u_nullptr),
					 _size(0),
					 _compare(Compare()),
					 _alloc(Allocator())
		{
			_nodeAlloc = std::allocator<node>();

			initNil();
			this->_root = this->nil;
		}
		rb_tree(const rb_tree &other) : _nodeAlloc(other._nodeAlloc)
		{
			_nodeAlloc = std::allocator<node>();
			initNil();
			*this = other;
		}
		~rb_tree()
		{
			clear();
			deleteNode(nil);
			nil = u_nullptr;
		}
		rb_tree &operator=(const rb_tree &other)
		{
			if (this != &other)
			{
				clear();
				_compare = other._compare;
				_alloc = other._alloc;
				_root = clone(other._root);
				_size = other._size;
			}
			return *this;
		}
		node *getRoot(void) { return _root; }
		size_type size(void) const { return _size; }
		size_type max_size(void) const { return this->_nodeAlloc.max_size(); }
		bool empty(void) const { return _size == 0; }
		void clear(void)
		{
			if (!_root->isNil())
				clearNodes(_root);
			_root = nil;
			_size = 0;
		}
		void rotateLeft(node *hinge)
		{
			rotateSide(hinge, LEFT);
		}
		void rotateRight(node *hinge)
		{
			rotateSide(hinge, RIGHT);
		}
		node *insert(const value_type &value, bool &wasInserted)
		{
			node *insertionParent = getInsertionParent(value.first);
			return insert(insertionParent, value, wasInserted);
		}
		node *insert(node *insertionParent, const value_type &value, bool &wasInserted)
		{
			node *nodeToInsert = nil;
			if (value.first == insertionParent->getKey() && !insertionParent->isNil())
			{
				wasInserted = false;
				return insertionParent;
			}
			nodeToInsert = newNode(value);
			nodeToInsert->parent = insertionParent;
			if (insertionParent->isNil())
				_root = nodeToInsert;
			else if (_compare(nodeToInsert->getKey(), insertionParent->getKey()))
				insertionParent->leftChild = nodeToInsert;
			else
				insertionParent->rightChild = nodeToInsert;
			insertFixup(nodeToInsert);
			++_size;
			wasInserted = true;
			return nodeToInsert;
		}
		size_type eraseNode(const key_type &key)
		{
			node *nodeToDelete = findNode(key);
			if (nodeToDelete->isNil())
				return 0;
			eraseNode(nodeToDelete);
			return 1;
		}
		void eraseNode(node *nodeToDelete)
		{
			node *nodeToFixup = nil;
			node *nodeToReplace = nodeToDelete;
			Color nodeToReplaceOriginalColor = nodeToReplace->color;

			if (nodeToDelete->leftChild->isNil())
			{
				nodeToFixup = nodeToDelete->rightChild;
				transplant(nodeToDelete, nodeToDelete->rightChild);
			}
			else if (nodeToDelete->rightChild->isNil())
			{
				nodeToFixup = nodeToDelete->leftChild;
				transplant(nodeToDelete, nodeToDelete->leftChild);
			}
			else
			{
				nodeToReplace = nodeToDelete->rightChild->getMin();
				nodeToReplaceOriginalColor = nodeToReplace->color;
				nodeToFixup = nodeToReplace->rightChild;
				if (nodeToReplace->parent == nodeToDelete && !nodeToFixup->isNil())
					nodeToFixup->parent = nodeToReplace;
				else
				{
					transplant(nodeToReplace, nodeToReplace->rightChild);
					nodeToReplace->rightChild = nodeToDelete->rightChild;
					if (!nodeToReplace->rightChild->isNil())
						nodeToReplace->rightChild->parent = nodeToReplace;
				}
				transplant(nodeToDelete, nodeToReplace);
				nodeToReplace->leftChild = nodeToDelete->leftChild;
				if (!nodeToReplace->leftChild->isNil())
					nodeToReplace->leftChild->parent = nodeToReplace;
				nodeToReplace->color = nodeToDelete->color;
			}
			if (nodeToReplaceOriginalColor == BLACK)
				deleteFixup(nodeToFixup);
			--_size;
			deleteNode(nodeToDelete);
		}
		node *findNode(const key_type &key)
		{
			return findNode(_root, key);
		}
		node *findNode(const key_type &key) const
		{
			return findNode(_root, key);
		}
		node *findNode(node *nodeToSearch, const key_type &key)
		{
			if (nodeToSearch->isNil() || nodeToSearch->getKey() == key)
				return nodeToSearch;
			if (_compare(key, nodeToSearch->getKey()))
				return findNode(nodeToSearch->leftChild, key);
			return findNode(nodeToSearch->rightChild, key);
		}
		node *findNode(node *nodeToSearch, const key_type &key) const
		{
			if (nodeToSearch->isNil() || nodeToSearch->getKey() == key)
				return nodeToSearch;
			if (_compare(key, nodeToSearch->getKey()))
				return findNode(nodeToSearch->leftChild, key);
			return findNode(nodeToSearch->rightChild, key);
		}
		node *lower_bound(const key_type &key)
		{
			return lower_bound(_root, key);
		}
		node *lower_bound(const key_type &key) const
		{
			return lower_bound(_root, key);
		}
		node *lower_bound(node *current_node, const key_type &key)
		{
			node *tmp = nil;

			if (current_node->isNil() || key == current_node->getKey())
				return current_node;
			if (_compare(current_node->getKey(), key))
				return lower_bound(current_node->rightChild, key);
			tmp = lower_bound(current_node->leftChild, key);
			if (tmp->isNil())
				return current_node;
			return tmp;
		}
		node *lower_bound(node *current_node, const key_type &key) const
		{
			node *tmp = nil;

			if (current_node->isNil() || key == current_node->getKey())
				return current_node;
			if (_compare(current_node->getKey(), key))
				return lower_bound(current_node->rightChild, key);
			tmp = lower_bound(current_node->leftChild, key);
			if (tmp->isNil())
				return current_node;
			return tmp;
		}
		node *upper_bound(const key_type &key)
		{
			return upper_bound(_root, key);
		}
		node *upper_bound(const key_type &key) const
		{
			return upper_bound(_root, key);
		}
		node *upper_bound(node *current_node, const key_type &key)
		{
			node *tmp = nil;

			if (current_node->isNil())
				return current_node;
			if (_compare(current_node->getKey(), key) || current_node->getKey() == key)
				return upper_bound(current_node->rightChild, key);
			tmp = upper_bound(current_node->leftChild, key);
			if (tmp->isNil())
				return current_node;
			return tmp;
		}
		node *upper_bound(node *current_node, const key_type &key) const
		{
			node *tmp = nil;

			if (current_node->isNil())
				return current_node;
			if (_compare(current_node->getKey(), key) || current_node->getKey() == key)
				return upper_bound(current_node->rightChild, key);
			tmp = upper_bound(current_node->leftChild, key);
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
		void printTree(std::string file = "tree_visualisation.mmd") const
		{
			std::ofstream myfile;

			myfile.open(file.c_str(), std::ios::out);
			myfile << "flowchart TD" << std::endl;
			myfile << "classDef RED fill:#FF0000,color:#FFFFFF;" << std::endl;
			myfile << "classDef BLACK fill:#000000,color:#FFFFFF;" << std::endl;
			if (_root)
				traverseTree(this->_root, myfile);
			else
				myfile << "Empty tree" << std::endl;
			myfile.close();
		}
		void swap(rb_tree &other)
		{
			node *tmp_root = other._root;
			node *tmp_nil = other.nil;
			size_type tmp_size = other._size;
			Compare tmp_compare = other._compare;
			Allocator tmp_alloc = other._alloc;

			other._root = this->_root;
			other.nil = this->nil;
			other._size = this->_size;
			other._compare = this->_compare;
			other._alloc = this->_alloc;

			this->_root = tmp_root;
			this->nil = tmp_nil;
			this->_size = tmp_size;
			this->_compare = tmp_compare;
			this->_alloc = tmp_alloc;
		}

	private:
		node *_root;
		node *nil;
		size_type _size;
		Compare _compare;
		Allocator _alloc;
		std::allocator<node> _nodeAlloc;

		void initNil(void)
		{
			// Init nil node
			value_type nilValue = ft::make_pair(Key(), T());

			nil = newNode(nilValue);
			nil->color = BLACK;
			nil->parent = nil;
			nil->leftChild = nil;
			nil->rightChild = nil;
		}

		node *newNode(const value_type &value)
		{
			node *newNode = _nodeAlloc.allocate(1);

			_alloc.construct(&newNode->value, value);
			newNode->leftChild = nil;
			newNode->rightChild = nil;
			newNode->parent = nil;
			newNode->color = RED;
			return newNode;
		}
		void deleteNode(node *node)
		{
			_alloc.destroy(&node->value);
			_nodeAlloc.deallocate(node, 1);
		}
		node *clone(node *src)
		{
			node *result = newNode(src->value);

			result->color = src->color;
			if (src->leftChild->isNil())
			{
				result->leftChild = nil;
			}
			else
			{
				result->leftChild = clone(src->leftChild);
				result->leftChild->parent = result;
			}
			if (src->rightChild->isNil())
			{
				result->rightChild = nil;
			}
			else
			{
				result->rightChild = clone(src->rightChild);
				result->rightChild->parent = result;
			}
			return result;
		}
		void transplant(node *oldNode, node *newNode)
		{
			if (oldNode->parent->isNil())
				_root = newNode;
			else if (oldNode->isALeftChild())
				oldNode->parent->leftChild = newNode;
			else
				oldNode->parent->rightChild = newNode;
			if (!newNode->isNil())
				newNode->parent = oldNode->parent;
		}
		void deleteFixup(node *x)
		{
			node *w = nil;

			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->leftChild)
				{
					w = x->parent->rightChild;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						rotateLeft(x->parent);
						w = x->parent->rightChild;
					}
					if (w->leftChild->color == BLACK && w->rightChild->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->rightChild->color == BLACK)
						{
							w->leftChild->color = BLACK;
							w->color = RED;
							rotateRight(w);
							w = x->parent->rightChild;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->rightChild->color = BLACK;
						rotateLeft(x->parent);
						x = _root;
					}
				}
				else
				{
					w = x->parent->leftChild;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						rotateRight(x->parent);
						w = x->parent->leftChild;
					}
					if (w->rightChild->color == BLACK && w->leftChild->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->leftChild->color == BLACK)
						{
							w->rightChild->color = BLACK;
							w->color = RED;
							rotateLeft(w);
							w = x->parent->leftChild;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->leftChild->color = BLACK;
						rotateRight(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}
		void clearNodes(node *nodeToDelete)
		{
			if (!nodeToDelete->leftChild->isNil())
				clearNodes(nodeToDelete->leftChild);
			if (!nodeToDelete->rightChild->isNil())
				clearNodes(nodeToDelete->rightChild);
			deleteNode(nodeToDelete);
			--_size;
		}
		void rotateSide(node *hinge, Side side)
		{
			node *movedNode = hinge->getChild(side == LEFT ? RIGHT : LEFT);
			if (side == LEFT)
				hinge->rightChild = movedNode->leftChild;
			else
				hinge->leftChild = movedNode->rightChild;
			if (!movedNode->getChild(side)->isNil())
				movedNode->getChild(side)->parent = hinge;
			movedNode->parent = hinge->parent;
			if (hinge->parent->isNil())
				_root = movedNode;
			else if (hinge->isALeftChild())
				hinge->parent->leftChild = movedNode;
			else
				hinge->parent->rightChild = movedNode;
			if (side == LEFT)
				movedNode->leftChild = hinge;
			else
				movedNode->rightChild = hinge;
			hinge->parent = movedNode;
		}
		node *getInsertionParent(const key_type &insertKey)
		{
			node *traversingTree = _root;
			node *result = nil;

			while (!traversingTree->isNil())
			{
				result = traversingTree;
				if (_compare(insertKey, traversingTree->getKey()))
					traversingTree = traversingTree->leftChild;
				else if (insertKey == traversingTree->getKey())
					return result;
				else
					traversingTree = traversingTree->rightChild;
			}
			return result;
		}
		void insertFixup(node *lastInsertedNode)
		{
			node *tmp;

			while (lastInsertedNode->parent->color == RED)
			{
				if (lastInsertedNode->parent == lastInsertedNode->parent->parent->leftChild)
				{
					tmp = lastInsertedNode->parent->parent->rightChild;
					if (tmp->color == RED)
					{
						lastInsertedNode->parent->color = BLACK;
						tmp->color = BLACK;
						lastInsertedNode->parent->parent->color = RED;
						lastInsertedNode = lastInsertedNode->parent->parent;
					}
					else
					{
						if (lastInsertedNode == lastInsertedNode->parent->rightChild)
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
					tmp = lastInsertedNode->parent->parent->leftChild;
					if (tmp->color == RED)
					{
						lastInsertedNode->parent->color = BLACK;
						tmp->color = BLACK;
						lastInsertedNode->parent->parent->color = RED;
						lastInsertedNode = lastInsertedNode->parent->parent;
					}
					else
					{
						if (lastInsertedNode == lastInsertedNode->parent->leftChild)
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
		void traverseTree(node *node, std::ofstream &file) const
		{
			file << node << "(" << node->getKey() << " - " << node->getMapped()
				 << ")" << std::endl;
			file << "class " << node << " " << (node->color == RED ? "RED": "BLACK") << ";"
				 << std::endl;
			if (!node->parent->isNil())
				file << node << "-->" << node->parent << std::endl;
			if (!node->leftChild->isNil())
			{
				file << node << "-.->" << node->leftChild << std::endl;
				traverseTree(node->leftChild, file);
			}
			if (!node->rightChild->isNil())
			{
				file << node << "==>" << node->rightChild << std::endl;
				traverseTree(node->rightChild, file);
			}
		}
	};
}