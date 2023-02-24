#pragma once

#include "utils.hpp"
#include "pair.hpp"
#include <memory>
#include <stdexcept>

namespace ft
{

	template <typename T, typename Compare = less<T> >
	class rb_node
	{

	public:
		typedef T value_type;
		typedef size_t size_type;

	public:
		rb_node *parent;
		rb_node *rightChild;
		rb_node *leftChild;
		Color color;
		value_type value;

		rb_node(void)
			: parent(u_nullptr), rightChild(u_nullptr), leftChild(u_nullptr), color(RED)
		{
			value = value_type();
		}
		rb_node(const value_type &value,
				rb_node *parent = u_nullptr,
				rb_node *right = u_nullptr,
				rb_node *left = u_nullptr,
				Color c = RED)
			: parent(parent), rightChild(right), leftChild(left), color(c), value(value)
		{
			return;
		}
		~rb_node()
		{
			return;
		}

		rb_node &operator=(const rb_node &other)
		{
			if (this == &other)
				return *this;
			this->parent = other.parent;
			this->rightChild = other.rightChild;
			this->leftChild = other.leftChild;
			this->color = other.color;
			this->value = other.value;
			return *this;
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
		rb_node *getChild(Side side)
		{
			if (side == LEFT)
				return this->leftChild;
			if (side == RIGHT)
				return this->rightChild;
			throw std::invalid_argument("Undefined side for getChild");
		}

		value_type &getValue(void) { return value; }
		const value_type &getValue(void) const { return value; }
		Color getColor(void) const { return color; }

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
		rb_node *getTreeSuccessor(const rb_node *currentNode = u_nullptr)
		{
			rb_node *tmp;

			if (currentNode == u_nullptr)
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
		rb_node *getTreeSuccessor(const rb_node *currentNode = u_nullptr) const
		{
			rb_node *tmp;

			if (currentNode == u_nullptr)
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
		rb_node *getTreePredecessor(const rb_node *currentNode = u_nullptr)
		{
			rb_node *tmp;

			if (currentNode == u_nullptr)
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
		rb_node *getTreePredecessor(const rb_node *currentNode = u_nullptr) const
		{
			rb_node *tmp;

			if (currentNode == u_nullptr)
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
	};

}