#pragma once

#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <stdio.h>

namespace ft
{

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		// Member types
		// typedef int											value_type;
		// typedef std::allocator<int>										allocator_type;
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef random_access_iterator<value_type>			iterator;
		typedef random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		allocator_type	_allocator;
		pointer			_start;
		pointer			_finish;
		pointer			_end_storage;
	public:
		/******************************************************************************/
		// Default constructor
		explicit vector(const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _start(u_nullptr), _finish(u_nullptr), _end_storage(u_nullptr){};
		// Fill constructor
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _start(u_nullptr), _finish(u_nullptr), _end_storage(u_nullptr)
		{
			_start = _allocator.allocate(n);
			_finish = _start;
			_end_storage = _finish + n;

			for (; n > 0; --n, (void)++_finish)
				_allocator.construct(_finish, val);
		};
		// Range constructor
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
			: _allocator(alloc), _start(u_nullptr), _finish(u_nullptr), _end_storage(u_nullptr)
		{
			reserve(last - first);
			for (; first != last; ++first)
				push_back(*first);
		};
		// Copy constructor
		vector(const vector &x)
			: _allocator(x._allocator), _start(u_nullptr), _finish(u_nullptr), _end_storage(u_nullptr)
		{
			_start = _allocator.allocate(x.size());
			_finish = _start;
			_end_storage = _finish + x.size();

			for (size_type i = 0; i < x.size(); ++i, (void)++_finish)
				_allocator.construct(_finish, x[i]);
		};
		~vector()
		{
			clear();
			_allocator.deallocate(_start, capacity());
		};
		vector &operator=(const vector &x)
		{
			if (this == &x)
				return *this;
			clear();
			_allocator.deallocate(_start, capacity());
			_start = _allocator.allocate(x.size());
			_finish = _start;
			_end_storage = _finish + x.size();

			for (size_type i = 0; i < x.size(); ++i, (void)++_finish)
				_allocator.construct(_finish, x[i]);
			return *this;
		};
/******************************************************************************/
		iterator begin()
		{
			return iterator(_start);
		};
		const_iterator begin() const
		{
			return const_iterator(_start);
		};
		iterator end()
		{
			return iterator(_finish);
		};
		const_iterator end() const
		{
			return const_iterator(_finish);
		};
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		};
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		};
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		};
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		};
/******************************************************************************/
		size_type size() const
		{
			return _finish - _start;
		};
		size_type max_size() const
		{
			return _allocator.max_size();
		};
		void resize(size_type n, value_type val = value_type())
		{
			if (n > size())
			{
				if (n > capacity())
					reserve(n);
				for (; n > size(); (void)++_finish)
					_allocator.construct(_finish, val);
			}
			else
			{
				for (; n < size(); (void)--_finish)
					_allocator.destroy(_finish);
			}
		};
		size_type capacity() const
		{
			return size_type(_end_storage - _start);
		}
		bool empty() const
		{
			return begin() == end();
		}
		void reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector::reserve");
			if (n > capacity())
			{
				pointer newStart = _allocator.allocate(n);
				if (size() > 0)
				{
					for (size_type i = 0; i < size(); ++i)
						_allocator.construct(newStart + i, _start[i]);
					_allocator.deallocate(_start, capacity());
				}
				size_type old_size = size();
				_start = newStart;
				_finish = _start + old_size;
				_end_storage = _start + n;
			}
		};
		reference operator[](size_type n)
		{
			return _start[n];
		}
		const_reference operator[](size_type n) const
		{
			return _start[n];
		}
		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector::at");
			return _start[n];
		};
		const_reference at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector::at");
			return _start[n];
		};
		reference front()
		{
			return *begin();
		}
		const_reference front() const
		{
			return *begin();
		}
		reference back()
		{
			return *(end() - 1);
		}
		const_reference back() const
		{
			return *(end() - 1);
		}
		/******************************************************************************/
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			clear();
			reserve(last - first);
			for (; first != last; ++first)
				push_back(*first);
		}
		void assign(size_type n, const value_type &val)
		{
			clear();
			reserve(n);
			for (; n > 0; --n)
				push_back(val);
		}
		void push_back(const value_type &val)
		{
			if (_finish == _end_storage)
			{
				if (capacity() == 0)
					reserve(1);
				else
					reserve(2 * capacity());
			}
			_allocator.construct(_finish, val);
			++_finish;
		}
		void pop_back()
		{
			--_finish;
			_allocator.destroy(_finish);
		}
		// TODO: DELETE
		void _print()
		{
			std::cout << "_print: ";
			for (iterator it = begin(); it != end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl;
		}
		// single element
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos_index = 0;
			if (_start != NULL)
				pos_index = &(*position) - _start;
			if (size_type(_end_storage - _finish) >= size() + 1)
			{
				for (size_type i = 0; i < pos_index; i++)
					_allocator.construct(_finish - i, *(_finish - i - 1));
				_finish++;
				_allocator.destroy(&(*position));
				_allocator.construct(&(*position), val);
			}
			else
			{
				size_type new_capacity = (size() >= capacity() ? capacity() * 2 : capacity());
				new_capacity += ( new_capacity == 0);
				
				pointer newStart = _allocator.allocate(new_capacity);
				for (size_type i = 0; i < pos_index; ++i)
					_allocator.construct(newStart + i, _start[i]);
				_allocator.construct(newStart + pos_index, val);
				for (size_type i = pos_index; i < size(); ++i)
					_allocator.construct(newStart + i + 1, _start[i]);
				size_type old_size = size();
				for (size_type i = 0; i < old_size; ++i)
					_allocator.destroy(_start + i);
				_allocator.deallocate(_start, capacity());
				_start = newStart;
				_finish = _start + old_size + 1;
				_end_storage = _start + new_capacity;
			}
			return (iterator(_start + pos_index));
		}
	private:
		// insert_range
		template <typename InputIterator>
		void _insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag,
						  typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			std::cerr << "Insert_range input iterator\n";
			for (; first != last; ++first, ++position)
				insert(position, *first);
			return ;
			/* size_type pos_len = &(*position) - _start;

			size_type newCapacity = size() >= capacity() ? (capacity() == 0 ? 1 : capacity() * 2) : capacity();
			pointer newStart = _allocator.allocate(newCapacity);
			size_type newSize = 0;
			for (; newSize < pos_len; ++newSize)
				_allocator.construct(newStart + newSize, _start[newSize]);
			// push_back to newStart all value of Input iterator
			for (; first != last; ++first, ++newSize)
			{
				if (newSize >= newCapacity)
				{
					newCapacity *= 2;
					// reserve capacity
					pointer newStart2 = _allocator.allocate(newCapacity);
					for (size_type i = 0; i < newSize; ++i)
						_allocator.construct(newStart2 + i, newStart[i]);
					_allocator.deallocate(newStart, newCapacity / 2);
					newStart = newStart2;
				}
				_allocator.construct(newStart + newSize, *first);
			}
			for (size_type i = pos_len; i < size(); ++i)
				_allocator.construct(newStart + i + (newSize - pos_len), _start[i]);
			_allocator.deallocate(_start, capacity());
			size_type old_size = size();
			_start = newStart;
			_finish = _start + old_size + (newSize - pos_len);
			_end_storage = _start + newCapacity; */
		}
		template <typename InputIterator>
		void _insert_range(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag,
						  typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			size_type n = std::distance(first, last);
			if (n == 0)
				return ;
			size_type pos_index = &(*position) - _start;
			if (size_type(_end_storage - _finish) >= n)
			{
				for(size_type i = 0; i < this->size() - pos_index; i++)
					_allocator.construct(_finish - i + (n - 1), *(_finish - i - 1));
				_finish += n;
				for (; first != last; first++, position++)
				{
					_allocator.destroy(&(*position));
					_allocator.construct(&(*position), *first);
				}
			}
			else
			{
				pointer newStart = pointer();
				pointer newFinish = pointer();
				pointer newEndStorage = pointer();
				// std::cout << "{ Capacity: " << capacity() << ", Size: " << size() << ", n: " << n << " }\n";
				if (size() * 2 < size() + n)
				{
					newStart = _allocator.allocate(size() + n);
					newFinish = newStart + size() + n;
					newEndStorage = newFinish;
				}
				else
				{
					newStart = _allocator.allocate(size() * 2);
					newFinish = newStart + size() + n;
					newEndStorage = newStart + size() * 2;
				}

				for (size_t i = 0; i < pos_index; i++)
					_allocator.construct(newStart + i, _start[i]);
				for (size_t i = 0; first != last; first++, i++)
					_allocator.construct(newStart + i + pos_index, *first);
				for (size_type i = pos_index; i < size(); i++)
					_allocator.construct(newStart + n + i, _start[i]);

				for (size_type i = 0; i < size(); i++)
					_allocator.destroy(_start + i);
				_allocator.deallocate(_start, _end_storage - _start);

				_start = newStart;
				_finish = newFinish;
				_end_storage = newEndStorage;
			}
		}
	public:
		// fill
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return ;
			if (n > this->max_size())
				throw (std::length_error("vector::insert (fill)"));
			size_type pos_len = &(*position) - _start;
			if (size_type(_end_storage - _finish) >= size() + n)
			{
				for (size_type i = 0; i < n; ++i)
					push_back(val);
				return;
			}
			else
			{
				size_type new_capacity = size() >= capacity() ? capacity() * 2 : capacity();
				pointer newStart = _allocator.allocate(new_capacity);
				for (size_type i = 0; i < pos_len; ++i)
					_allocator.construct(newStart + i, _start[i]);
				for (size_type i = pos_len; i < pos_len + n; ++i)
					_allocator.construct(newStart + i, val);
				for (size_type i = pos_len; i < size(); ++i)
					_allocator.construct(newStart + i + n, _start[i]);
				_allocator.deallocate(_start, capacity());
				size_type old_size = size();
				_start = newStart;
				_finish = _start + old_size + n;
				_end_storage = _start + new_capacity;
			}
		}
		// range Input Iterator
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			_insert_range(position, first, last, ft::iterator_category(first));
		}

		iterator erase(iterator position)
		{
			pointer tmp = &(*position);
			_allocator.destroy(tmp);
			for (pointer it = tmp; it != _finish - 1; ++it)
				*it = *(it + 1);
			--_finish;
			return iterator(tmp);
		}
		iterator erase(iterator first, iterator last)
		{
			pointer tmp = &(*first);
			for (pointer it = tmp; it != &(*last); ++it)
				_allocator.destroy(it);
			for (pointer it = tmp; it != _finish - (last - first); ++it)
				*it = *(it + (last - first));
			_finish -= (last - first);
			return iterator(tmp);
		}
		void swap(vector &x)
		{
			pointer tmp_start = _start;
			pointer tmp_finish = _finish;
			pointer tmp_end_storage = _end_storage;
			_start = x._start;
			_finish = x._finish;
			_end_storage = x._end_storage;
			x._start = tmp_start;
			x._finish = tmp_finish;
			x._end_storage = tmp_end_storage;
		}
		void clear()
		{
			if (size() <= 0)
				return;

			for (iterator it = begin(); it != end(); ++it)
				_allocator.destroy(&(*it));
			_finish = _start;
		}
		allocator_type get_allocator() const
		{
			return _allocator;
		}

	}; // class vector
} // namespace ft