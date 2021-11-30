/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:47:31 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/29 17:59:34 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef FT_VERSION
# define FT_VERSION 1
#endif

#if FT_VERSION == 1
#define TESTED_NAMESPACE ft
# include "map.hpp"
#else
# include <map>
#define TESTED_NAMESPACE std
#endif

#include <map>

#ifdef FT_VERSION
template <typename T>
class foo {
        public:
                typedef T       value_type;

                foo(void) : value(), _verbose(false) { };
                foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
                foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
                ~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
                void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
                void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
                foo &operator=(value_type src) { this->value = src; return *this; };
                foo &operator=(foo const &src) {
                        if (this->_verbose || src._verbose)
                                std::cout << "foo::operator=(foo) CALLED" << std::endl;
                        this->value = src.value;
                        return *this;
                };
                value_type      getValue(void) const { return this->value; };
                void            switchVerbose(void) { this->_verbose = !(this->_verbose); };

                operator value_type(void) const {
                        return value_type(this->value);
                }
        private:
                value_type      value;
                bool            _verbose;
};
#endif

#define T1 char
#define T2 foo<float>
typedef TESTED_NAMESPACE::map<T1, T2> _map;
typedef _map::const_iterator const_it;

static unsigned int i = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void	ft_comp(const _map &mp, const const_it &it1, const const_it &it2)
{
	bool res[2];

	std::cout << "\t-- [" << ++i << "] --" << std::endl;
	res[0] = mp.key_comp()(it1->first, it2->first);
	res[1] = mp.value_comp()(*it1, *it2);
	std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

#include <list>
#include <iostream>

void	test(void)
{
	_map	mp;

	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;
	printSize(mp);

	for (const_it it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (const_it it2 = mp.begin(); it2 != mp.end(); ++it2)
			ft_comp(mp, it1, it2);

	printSize(mp);
}


int main(void)
{
	test();
	return (0);
}