#pragma once

namespace ft
{
	template <bool IsConst, typename NonConst, typename Const>
    struct ternaire {};

    template <typename NonConst, typename Const>
    struct ternaire<false, NonConst, Const>
    {
        typedef NonConst type;
    };

    template <typename NonConst, typename Const>
    struct ternaire<true, NonConst, Const>
    {
        typedef Const type;
    };
	enum Color
	{
		RED = false,
		BLACK = true
	};
	enum Side
	{
		LEFT = false,
		RIGHT = true
	};

	typedef long unsigned int size_t;
	typedef long int ptrdiff_t;

	static class nullptr_t
	{
	public:
		/*
		** @brief For conversion to any type
		** of null non-member pointer.
		*/
		template <class T>
		operator T *() const { return (0); }

		/*
		** @brief For conversion to any type of null
		** member pointer.
		*/
		template <class C, class T>
		operator T C::*() const { return (0); }

	private:
		/*
		** @brief It's imposible to get an address of
		** a nullptr.
		*/
		void operator&() const;
	} u_nullptr = {};

	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator()(const T &lhs, const T &rhs) const
		{
			return (lhs < rhs);
		}
	};

	template <class T>
	struct greater : binary_function<T, T, bool>
	{
		bool operator()(const T &lhs, const T &rhs) const
		{
			return (lhs > rhs);
		}
	};

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator2 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator2 last1,
								 InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2)) // or: if (!pred(*first1,*first2)), for version 2
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
} // namespace ft