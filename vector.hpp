#pragma once

#include <memory>
#include "type_traits.hpp"
#include "reverse_iterator.hpp"
#include "distance.hpp"
#include <stdexcept>

namespace ft
{

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		// Member types
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef pointer										iterator;
		typedef const_pointer								const_iterator;
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
			reserve(ft::distance(first, first));
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
			if (n > max_size())
				throw std::length_error("vector::resize");
			if (n > size())
			{
				if (n > capacity())
					reserve(n);
				for (; n > size(); (void)++_finish)
					_allocator.construct(_finish, val);
			}
			else
			{
				for (; n < size();)
					_allocator.destroy(--_finish);
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
/******************************************************************************/
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
					{
						_allocator.construct(newStart + i, _start[i]);
						_allocator.destroy(_start + i);
					}
				}
				_allocator.deallocate(_start, capacity());
				size_type old_size = size();
				_start = newStart;
				_finish = _start + old_size;
				_end_storage = _start + n;
			}
		};
/******************************************************************************/
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
	private:
		template <class InputIterator>
		void _assign(InputIterator first, InputIterator last,  std::input_iterator_tag,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			clear();
			for (; first != last; ++first)
				push_back(*first);
		}

		template <class InputIterator>
		void _assign(InputIterator first, InputIterator last,  std::forward_iterator_tag,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			clear();
			reserve(ft::distance(first, last));
			for (; first != last; ++first)
				push_back(*first);
		}
	public:
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			_assign(first, last, ft::iterator_category(first));
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
		// single element
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos_index = &(*position) - _start;
			if (size_type(_end_storage - _finish) >= size() + 1)
			{
				for (size_type i = 0; i < this->size() - pos_index; i++)
				{
					_allocator.construct(_finish - i, *(_finish - i - 1));
					_allocator.destroy(_finish - i - 1);
				}
				++_finish;
				_allocator.construct(&(*position), val);
			}
			else
			{
				vector<value_type> tmp;

				tmp.reserve(size());
				for (iterator it = begin(); it != position; ++it)
					tmp.push_back(*it);
				tmp.push_back(val);
				for (iterator it = position; it != end(); ++it)
					tmp.push_back(*it);
				swap(tmp);
			}
			return (iterator(_start + pos_index));
		}

	private:
		// insert_range
		template <typename InputIterator>
		void _insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag,
						   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			vector tmp;
			tmp.reserve(size());
			for (iterator it = begin(); it != position; ++it)
				tmp.push_back(*it);
			for (; first != last; ++first)
				tmp.push_back(*first);
			for (iterator it = position; it != end(); ++it)
				tmp.push_back(*it);
			swap(tmp);
		}
		template <typename InputIterator>
		void _insert_range(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag,
						   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			size_type n = std::distance(first, last);
			if (n == 0)
				return;
			size_type pos_index = &(*position) - _start;
			if (size_type(_end_storage - _finish) >= n)
			{
				for (size_type i = 0; i < this->size() - pos_index; i++)
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
				vector<value_type>	tmp;
				tmp.reserve(size() + n);
				for (iterator it = begin(); it != position; ++it)
					tmp.push_back(*it);
				for (; first != last; ++first)
					tmp.push_back(*first);
				for (iterator it = position; it != end(); ++it)
					tmp.push_back(*it);
				swap(tmp);
			}
		}

	public:
		// fill
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return;
			if (n > this->max_size())
				throw(std::length_error("vector::insert (fill)"));

			vector<value_type>	tmp;
			if (size_type(_end_storage - _finish) >= n)
				tmp.reserve(capacity());
			else
				tmp.reserve(size() + n);
			for (iterator it = begin(); it != position; ++it)
				tmp.push_back(*it);
			for (; n != 0; --n)
				tmp.push_back(val);
			for (iterator it = position; it != end(); ++it)
				tmp.push_back(*it);
			swap(tmp);
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
		// relational operators


	}; // class vector

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return rhs < lhs;
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

} // namespace ft