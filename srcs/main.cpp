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

#define T1 int
#define T2 std::string

TESTED_NAMESPACE::map<T1, T2> mp;
TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end();


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

void	ft_find(T1 const &k)
{
	TESTED_NAMESPACE::map<T1, T2>::iterator ret = mp.find(k);

	if (ret != it)
		printPair(ret);
	else
		std::cout << "map::find(" << k << ") returned end()" << std::endl;
}

void	ft_count(T1 const &k)
{
	std::cout << "map::count(" << k << ")\treturned [" << mp.count(k) << "]" << std::endl;
}
#include <list>
#include <iostream>

void	test(void)
{
	mp[42] = "fgzgxfn";
	std::cout << "HEY HEY HEY\n";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	printSize(mp);

	std::cout << "\t-- FIND --" << std::endl;
	ft_find(12);
	ft_find(3);
	ft_find(35);
	ft_find(90);
	ft_find(100);

	std::cout << "\t-- COUNT --" << std::endl;
	ft_count(-3);
	ft_count(12);
	ft_count(3);
	ft_count(35);
	ft_count(90);
	ft_count(100);

	mp.find(27)->second = "newly inserted mapped_value";

	printSize(mp);

	TESTED_NAMESPACE::map<T1, T2> const c_map(mp.begin(), mp.end());
	std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
	std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
}


int main(void)
{
	test();
	return (0);
}