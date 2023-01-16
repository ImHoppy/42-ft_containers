#pragma once

#include "vector.hpp"

namespace ft {
	template <class T, class Container = vector<T> >
	class stack {
	public:
		typedef T							value_type;
		typedef Container					container_type;
		typedef typename container_type::size_type	size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
	private:
		container_type	_ctnr;
	public:
		explicit stack(const container_type &ctnr = container_type()) : _ctnr(ctnr) {}
		~stack() {};
		bool empty() const { return _ctnr.empty(); }
		size_type size() const { return _ctnr.size(); }
		reference top() { return _ctnr.back(); }
		const_reference top() const { return _ctnr.back(); }
		void push(const value_type &val) { _ctnr.push_back(val); }
		void pop() { _ctnr.pop_back(); }

		template <class T1, class Container1>
		friend bool operator==(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
		template <class T1, class Container1>
		friend bool operator!=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
		template <class T1, class Container1>
		friend bool operator<(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
		template <class T1, class Container1>
		friend bool operator<=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
		template <class T1, class Container1>
		friend bool operator>(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
		template <class T1, class Container1>
		friend bool operator>=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._ctnr == rhs._ctnr; }
	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._ctnr != rhs._ctnr; }
	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._ctnr < rhs._ctnr; }
	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._ctnr <= rhs._ctnr; }
	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._ctnr > rhs._ctnr; }
	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._ctnr >= rhs._ctnr; }
	
}
