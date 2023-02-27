#include <iostream>
#include <string>
#include <list>
#ifndef USE_STD
#include "set.hpp"
using namespace ft;
#else
#include <set>
using namespace std;
#endif

template <typename M>
void	printSize(M const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	if (print_content)
	{
		typename M::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
}

template <typename M>
void	comp(const M &mp, const typename M::const_iterator &it1, const typename M::const_iterator &it2)
{
	bool res[2];

	res[0] = mp.key_comp()(*it1, *it2);
	res[1] = mp.value_comp()(*it1, *it2);
	std::cout << "with [" << *it1 << " and " << *it2 << ": ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}
template <typename T>
typename T::iterator get_itn(T &c, int r, typename T::iterator min, std::forward_iterator_tag)
{
	typename T::iterator ret = min;
	int pos = 0;
	unsigned long int	m = c.size();
	for (typename T::iterator it = min; it != c.end(); it++, m--);
	if (c.size() != m)
		pos = r % (c.size() - m);
	for (int i = 0; i < pos; i++)
		ret++;
	return (ret);
}

template <typename T>
typename T::iterator get_itn(T &c, int r, typename T::iterator min, std::random_access_iterator_tag)
{
	if (min == c.end())
		return (c.end());
	return (min + (c.end() - min) % r);
}

/**
 * @def get an iterator at a random position of the container c after min based on the random number r
 * @param c the container to get the iterator from
 * @param r a random number
 * @param min the returned iterator is guaranteed to be min or after min
 */
template <typename T>
typename T::iterator get_itn(T &c, int r, typename T::iterator min)
{
	return (get_itn(c, r, min, typename std::iterator_traits<typename T::iterator>::iterator_category()));
}

/**
 * @def get an iterator at a random position of the container c based on the random number r
 * @param c the container to get the iterator from
 * @param r a random number
 */
template <typename T>
typename T::iterator get_itn(T &c, int r)
{
	return (get_itn(c, r, c.begin()));
}

template <typename T>
void test_operator(T c1, T c2)
{
	std::cout << "c1 == c2: " << (c1 == c2) << "\t";
	std::cout << "c1 != c2: " << (c1 != c2) << "\t";
	std::cout << "c1 < c2: " << (c1 < c2) << "\t";
	std::cout << "c1 <= c2: " << (c1 <= c2) << "\t";
	std::cout << "c1 > c2: " << (c1 > c2) << "\t";
	std::cout << "c1 >= c2: " << (c1 >= c2) << std::endl;
}

void set_main() {
	std::cout << "# Set\n";
	set<float>	mp;

	mp.insert(2.3);
	mp.insert(1.4);
	mp.insert(0.3);
	mp.insert(4.2);
	for (set<float>::iterator it = mp.begin(); it != mp.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "# Set Size\n";
	printSize(mp);

	std::cout << "# Set Comp\n";
	for (set<float>::const_iterator  it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (set<float>::const_iterator  it2 = mp.begin(); it2 != mp.end(); ++it2)
			comp(mp, it1, it2);

	std::cout << "# Set Size\n";
	printSize(mp);

	std::cout << "# Set Tree\n";
	{
		typedef set<std::string> C;
		C m1;
		C m2;
		m1.insert("Coucou");
		{
			C m3(m2);
			std::cout << "m3:\n";
			for (set<std::string>::iterator it = m3.begin(); it != m3.end(); ++it)
				std::cout << *it << std::endl;
			m2 = m1;
			std::cout << "m2:\n";
			for (set<std::string>::iterator it = m2.begin(); it != m2.end(); ++it)
				std::cout << *it << std::endl;
			m1 = m3;
			std::cout << "m1:\n";
			for (set<std::string>::iterator it = m1.begin(); it != m1.end(); ++it)
				std::cout << *it << std::endl;
		}
		std::cout << ("printing m1: ");
		for (set<std::string>::iterator it = m1.begin(); it != m1.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << ("printing m2: ");
		for (set<std::string>::iterator it = m2.begin(); it != m2.end(); ++it)
			std::cout << *it << std::endl;
		m1.insert("aaloa");
		std::cout << ("printing m1: ");
		for (set<std::string>::iterator it = m1.begin(); it != m1.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << ("printing m2: ");
		for (set<std::string>::iterator it = m2.begin(); it != m2.end(); ++it)
			std::cout << *it << std::endl;
		#ifndef USE_STD
			// m1.printTree("m1.mmd");
			// m2.printTree("m2.mmd");
		#endif
	}
	std::cout << "# Set iterator with other containers\n";
	{
		typedef set<std::string> C;
		C m1;

		m1.insert("hola amigo");
		m1.insert("eqaha");
		m1.insert("ujxwl");
		m1.insert("rfecq");
		m1.insert("amigo de la tornada");
		m1.insert("shwtx");
		m1.insert("ewrpj");
		m1.insert("amigo de pepito");
		m1.insert("pgtrb");
		m1.insert("amigo de pepito");

		std::list<C::value_type> list(m1.begin(), m1.end());
		std::cout << "list: " << list.size() << " m1: " << m1.size() << std::endl;

		for (std::list<C::value_type>::iterator it = list.begin(); it != list.end(); ++it)
			std::cout << *it << std::endl;
		for (C::iterator it = m1.begin(); it != m1.end(); ++it)
			std::cout << *it << std::endl;
	}
	std::cout << "# Set relational operator int\n";
	{
		typedef set<int> C;
		C m1;
		C m2;

		m1.insert(1);
		m1.insert(2);
		m1.insert(3);
		m1.insert(4);

		m2.insert(1);
		test_operator(m1, m2);
		m2.insert(2);
		m2.insert(3);
		m2.insert(4);
		test_operator(m1, m2);

		m2.insert(5);
		test_operator(m1, m2);

		m2.insert(4);
		test_operator(m1, m2);

		m2.insert(4);
		m1.insert(5);
		test_operator(m1, m2);

		m1.insert(4);
		test_operator(m1, m2);
	}
	std::cout << "# Set relational operator string\n";
	{
		typedef set<std::string> C;
		C m1;
		C m2;
		m1.insert("amigo de la tornada");
		m1.insert("amigo de pepito");
		m1.insert("bytwp");
		m1.insert("cewtt");
		m1.insert("dos");
		m1.insert("dsivl");
		m1.insert("olrlb");
		m1.insert("qyvtb");
		m1.insert("rfecq");
		m1.insert("shwtx");
		m1.insert("sjgal");

		m2.insert("amigo de pepito");
		m2.insert("ceivz");
		m2.insert("qvlex");
		m2.insert("wwnuu");
		m2.insert("wxewz");
		m2.insert("xczni");

		test_operator(m1, m2);
	}

}