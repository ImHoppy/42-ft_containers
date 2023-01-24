#pragma once

#include "utils.hpp"
#include "pair.hpp"
#include <memory>

namespace ft
{

	template <typename Key, typename T, typename Compare = std::less<Key>,
			  typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class rb_node
	{

	public:
		typedef const Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef std::size_t size_type;

		rb_node(void) : parent(NULL), rightChild(NULL), leftChild(NULL), color(RED)
		{
			value.first = Key();
			value.second = T();
		}
		rb_node(value_type &value) : parent(NULL), rightChild(NULL), leftChild(NULL), color(RED), value(value)
		{
			return;
		}
		~rb_node()
		{
			return;
		}

		rb_node &operator=(const rb_node &other)
		{
			this->parent = other.parent;
			this->rightChild = other.rightChild;
			this->leftChild = other.leftChild;
			this->color = other.color;
		}

		bool isNil(void) const
		{
			return this->parent == this;
		}
		bool isALeftChild(void) const
		{
			return this->parent->leftChild == this;
		}
		bool isARightChild(void) const
		{
			return this->parent->rightChild == this;
		}
		rb_node *getChild(int side)
		{
			if (side == LEFT)
				return this->leftChild;
			if (side == RIGHT)
				return this->rightChild;
			throw std::invalid_argument("You can only use value LEFT (0) and RIGHT (1)");
		}

		value_type &getValue(void) { return value; }
		const value_type &getValue(void) const { return value; }
		const key_type &getKey(void) const { return value.first; }
		mapped_type &getMapped(void) { return value.second; }
		const mapped_type &getMapped(void) const { return value.second; }
		std::string getColorAsString(void) const
		{
			if (this->color == RED)
				return std::string("RED");
			else
				return std::string("BLACK");
		}
		char getColorAsChar(void) const
		{
			return this->color;
		}

		rb_node *getMin(void)
		{
			rb_node *treeMinimum = this;

			while (!treeMinimum->leftChild->isNil())
				treeMinimum = treeMinimum->leftChild;
			return treeMinimum;
		}
		rb_node *getMin(void) const
		{
			rb_node *treeMinimum = this;

			while (!treeMinimum->leftChild->isNil())
				treeMinimum = treeMinimum->leftChild;
			return treeMinimum;
		}
		rb_node *getMax(void)
		{
			rb_node *treeMaximum = this;

			while (!treeMaximum->rightChild->isNil())
				treeMaximum = treeMaximum->rightChild;
			return treeMaximum;
		}
		rb_node *getMax(void) const
		{
			rb_node *treeMaximum = this;

			while (!treeMaximum->rightChild->isNil())
				treeMaximum = treeMaximum->rightChild;
			return treeMaximum;
		}
		rb_node *getTreeSuccessor(const rb_node *currentNode = NULL)
		{
			rb_node *tmp;

			if (currentNode == NULL)
				currentNode = this;
			if (!currentNode->rightChild->isNil())
				return currentNode->rightChild->getMin();
			tmp = currentNode->parent;
			while ((!tmp->isNil()) && currentNode == tmp->rightChild)
			{
				currentNode = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}
		rb_node *getTreeSuccessor(const rb_node *currentNode = NULL) const
		{
			rb_node *tmp;

			if (currentNode == NULL)
				currentNode = this;
			if (!currentNode->rightChild->isNil())
				return currentNode->rightChild->getMin();
			tmp = currentNode->parent;
			while ((!tmp->isNil()) && currentNode == tmp->rightChild)
			{
				currentNode = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}
		rb_node *getTreePredecessor(const rb_node *currentNode = NULL)
		{
			rb_node *tmp;

			if (currentNode == NULL)
				currentNode = this;
			if (!currentNode->leftChild->isNil())
				return currentNode->leftChild->getMax();
			tmp = currentNode->parent;
			while ((!tmp->isNil()) && currentNode == tmp->leftChild)
			{
				currentNode = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}
		rb_node *getTreePredecessor(const rb_node *currentNode = NULL) const
		{
			rb_node *tmp;

			if (currentNode == NULL)
				currentNode = this;
			if (!currentNode->leftChild->isNil())
				return currentNode->leftChild->getMax();
			tmp = currentNode->parent;
			while ((!tmp->isNil()) && currentNode == tmp->leftChild)
			{
				currentNode = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}

	public:
		rb_node *parent;
		rb_node *rightChild;
		rb_node *leftChild;
		Color color;
		value_type value;
	};

}