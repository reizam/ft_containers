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

#define T1 int
#define T2 std::string
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator iterator;
#define _pair TESTED_NAMESPACE::pair
static int iter = 0;


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
template <typename MAP, typename U>
void	ft_insert(MAP &mp, U param)
{
	_pair<iterator, bool> tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param);
	std::cout << "insert return: " << printPair(tmp.first);
	std::cout << "Created new node: " << tmp.second << std::endl;
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_insert(MAP &mp, U param, V param2)
{
	iterator tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
	std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}

#include <list>
#include <iostream>

void	test(void)
{
	TESTED_NAMESPACE::map<int, std::string> mp;
(void)iter;

	// ft_insert(mp, T3(42, "lol"));
	// ft_insert(mp, T3(42, "mdr"));

	// ft_insert(mp, T3(50, "mdr"));
	// ft_insert(mp, T3(35, "funny"));

	// ft_insert(mp, T3(45, "bunny"));
	// ft_insert(mp, T3(21, "fizz"));
	// ft_insert(mp, T3(38, "buzz"));

	// ft_insert(mp, mp.begin(), T3(55, "fuzzy"));

	// ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
	// ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
	// ft_insert(mp2, mp2.end(), T3(1500, "World"));
}


int main(void)
{
	test();
	return (0);
}