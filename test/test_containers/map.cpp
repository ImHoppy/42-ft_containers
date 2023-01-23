#include <iostream>
#include <string>

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
	std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

void map_main() {
	std::cout << "# Map\n";
	map<char, float>	mp;

	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;

	std::cout << "# Map Size\n";
	printSize(mp);

	std::cout << "# Map IT\n";
	for (map<char, float>::const_iterator  it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (map<char, float>::const_iterator  it2 = mp.begin(); it2 != mp.end(); ++it2)
			comp(mp, it1, it2);

	std::cout << "# Map Size\n";
	printSize(mp);
#ifndef USE_STD

	std::cout << "# Map Tree\n";
	mp.printTree();
#endif
}