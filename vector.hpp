#pragma once

#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

	template< class T, class Alloc = std::allocator<T> >
	class vector {
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
		explicit vector(const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _start(NULL), _finish(NULL), _end_storage(NULL)
		{};
		// Fill constructor
		explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _start(NULL), _finish(NULL), _end_storage(NULL)
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
				const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		: _allocator(alloc), _start(NULL), _finish(NULL), _end_storage(NULL)
		{
			reserve(last - first);
			for (; first != last; ++first)
				push_back(*first);
		};
		// Copy constructor
		vector(const vector& x)
		: _allocator(x._allocator), _start(NULL), _finish(NULL), _end_storage(NULL)
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
		vector& operator=(const vector& x)
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
		{ return size_type(_end_storage - _start); }
		bool empty() const
		{ return begin() == end(); }
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
		{ return _start[n]; }
		const_reference operator[](size_type n) const
		{ return _start[n]; }
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
		{ return *begin(); }
		const_reference front() const
		{ return *begin(); }
		reference back()
		{ return *(end() - 1); }
		const_reference back() const
		{ return *(end() - 1); }
/******************************************************************************/
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		{
			clear();
			reserve(last - first);
			for (; first != last; ++first)
				push_back(*first);
		}
		void assign(size_type n, const value_type& val)
		{
			clear();
			reserve(n);
			for (; n > 0; --n)
				push_back(val);
		}
		void push_back(const value_type& val)
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
		iterator insert(iterator position, const value_type& val)
		{
			size_type pos_len = &(*position) - _start;
			if (size_type(_end_storage - _finish) >= size() + 1)
			{
				push_back(val);
				return end() - 1;
			}
			else
			{
				size_type new_capacity = size() >= capacity() ? capacity() * 2 : capacity();
				pointer newStart = _allocator.allocate(new_capacity);
				for (size_type i = 0; i < pos_len; ++i)
					_allocator.construct(newStart + i, _start[i]);
				_allocator.construct(newStart + pos_len, val);
				for (size_type i = pos_len; i < size(); ++i)
					_allocator.construct(newStart + i + 1, _start[i]);
				_allocator.deallocate(_start, capacity());
				size_type old_size = size();
				_start = newStart;
				_finish = _start + old_size + 1;
				_end_storage = _start + new_capacity;
			}
			return (iterator(_start + pos_len));
		}
		// fill
		void insert(iterator position, size_type n, const value_type& val)
		{
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
		// insert_range
		template <typename InputIterator>
		void insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		{
			size_type pos_len = &(*position) - _start;
			size_type n = 1;
			if (size_type(_end_storage - _finish) >= size() + n)
			{
				for (size_type i = 0; first != last; ++i, ++first)
					push_back(*first);
				return;
			}
			else
			{
				size_type new_capacity = size() >= capacity() ? capacity() * 2 : capacity();
				pointer newStart = _allocator.allocate(new_capacity);
				for (size_type i = 0; i < pos_len; ++i)
					_allocator.construct(newStart + i, _start[i]);
				for (size_type i = pos_len; i < pos_len + n; ++i, ++first)
					_allocator.construct(newStart + i, *first);
				for (size_type i = pos_len; i < size(); ++i)
					_allocator.construct(newStart + i + n, _start[i]);
				_allocator.deallocate(_start, capacity());
				size_type old_size = size();
				_start = newStart;
				_finish = _start + old_size + n;
				_end_storage = _start + new_capacity;
			}
		}
		template <typename InputIterator>
		void insert_range(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		{
			size_type pos_len = &(*position) - _start;
			size_type n = last - first;
			if (size_type(_end_storage - _finish) >= size() + n)
			{
				for (size_type i = 0; i < n; ++i, ++first)
					push_back(*first);
				return;
			}
			else
			{
				size_type new_capacity = size() >= capacity() ? capacity() * 2 : capacity();
				pointer newStart = _allocator.allocate(new_capacity);
				for (size_type i = 0; i < pos_len; ++i)
					_allocator.construct(newStart + i, _start[i]);
				for (size_type i = pos_len; i < pos_len + n; ++i, ++first)
					_allocator.construct(newStart + i, *first);
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
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		{
			insert_range(position, first, last, ft::iterator_category(first));
		}

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector& x)
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
		{ return _allocator; }


	}; // class vector
} // namespace ft