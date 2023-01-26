#include <iostream>
#include <string>
#include <set>
#ifndef USE_STD
#include "map.hpp"

using namespace ft;
#else
#include <map>
using namespace std;
#endif

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename M>
void	printSize(M const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename M::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
}

template <typename M>
void	comp(const M &mp, const typename M::const_iterator &it1, const typename M::const_iterator &it2)
{
	bool res[2];

	res[0] = mp.key_comp()(it1->first, it2->first);
	res[1] = mp.value_comp()(*it1, *it2);
	std::cout << "with [" << it1->first << " and " << it2->first << ": ";
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

void map_main() {
	std::cout << "# Map\n";
	map<char, float>	mp;

	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;
	for (map<char, float>::iterator it = mp.begin(); it != mp.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;

	std::cout << "# Map Size\n";
	printSize(mp);

	std::cout << "# Map Comp\n";
	for (map<char, float>::const_iterator  it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (map<char, float>::const_iterator  it2 = mp.begin(); it2 != mp.end(); ++it2)
			comp(mp, it1, it2);

	std::cout << "# Map Size\n";
	printSize(mp);

	std::cout << "# Map Tree\n";
	{
		typedef map<std::string, std::string> C;
		C m1;
		C m2;
		m1.insert(make_pair("Coucou", "hi"));
		{
			C m3(m2);
			std::cout << "m3:\n";
			for (map<std::string, std::string>::iterator it = m3.begin(); it != m3.end(); ++it)
				std::cout << it->first << " " << it->second << std::endl;
			m2 = m1;
			std::cout << "m2:\n";
			for (map<std::string, std::string>::iterator it = m2.begin(); it != m2.end(); ++it)
				std::cout << it->first << " " << it->second << std::endl;
			m1 = m3;
			std::cout << "m1:\n";
			for (map<std::string, std::string>::iterator it = m1.begin(); it != m1.end(); ++it)
				std::cout << it->first << " " << it->second << std::endl;
		}
		std::cout << ("printing m1: ");
		for (map<std::string, std::string>::iterator it = m1.begin(); it != m1.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << ("printing m2: ");
		for (map<std::string, std::string>::iterator it = m2.begin(); it != m2.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;
		m1["hola amigo"] = "aaloa";
		std::cout << ("printing m1: ");
		for (map<std::string, std::string>::iterator it = m1.begin(); it != m1.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << ("printing m2: ");
		for (map<std::string, std::string>::iterator it = m2.begin(); it != m2.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;
		#ifndef USE_STD
			m1.printTree("m1.mmd");
			m2.printTree("m2.mmd");
		#endif
	}
	std::cout << "# Map iterator with other containers\n";
	{
		typedef map<std::string, std::string> C;
		C m1;

		m1["hola amigo"] = "aaloa";
		m1["eqaha"];
		m1["ujxwl"] = "eebzm";
		m1["rfecq"];
		m1["amigo de la tornada"] = "apicf";
		m1["shwtx"];
		m1["ewrpj"] = "wkwin";
		m1["amigo de pepito"];
		m1["pgtrb"] = "ijxna";
		m1["amigo de pepito"];

		std::set<C::value_type> set(m1.begin(), m1.end());
		std::cout << "set: " << set.size() << " m1: " << m1.size() << std::endl;

		for (std::set<C::value_type>::iterator it = set.begin(); it != set.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;
		for (C::iterator it = m1.begin(); it != m1.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << "# Map relational operator int\n";
	{
		typedef map<int, int> C;
		C m1;
		C m2;

		m1[1] = 1;
		m1[2] = 2;
		m1[3] = 3;
		m1[4] = 4;

		m2[1] = 1;
		test_operator(m1, m2);
		m2[2] = 2;
		m2[3] = 3;
		m2[4] = 4;
		test_operator(m1, m2);

		m2[5] = 5;
		test_operator(m1, m2);
		
		m2[4] = 5;
		test_operator(m1, m2);

		m2[4] = 4;
		m1[5] = 5;
		test_operator(m1, m2);

		m1[5] = 4;
		test_operator(m1, m2);
	}
	std::cout << "# Map relational operator string\n";
	{
		typedef map<std::string, std::string> C;
		C m1;
		C m2;
		m1["amigo de la tornada"] = "vsjcp";
		m1["amigo de pepito"] = "queob";
		m1["bytwp"] = "soxeu";
		m1["cewtt"];
		m1["dos"] = "qjqbl";
		m1["dsivl"] = "llhfj";
		m1["olrlb"] = "oixuu";
		m1["qyvtb"];
		m1["rfecq"];
		m1["shwtx"];
		m1["sjgal"];

		m2["amigo de pepito"] = "atencion";
		m2["ceivz"] = "atencion";
		m2["qvlex"] = "ifbay";
		m2["wwnuu"];
		m2["wxewz"];
		m2["xczni"];

		test_operator(m1, m2);
	}

}