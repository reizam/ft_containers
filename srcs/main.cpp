/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:47:31 by kmazier           #+#    #+#             */
/*   Updated: 2021/12/01 16:01:17 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

#ifndef FT_VERSION
# define FT_VERSION 1
#endif

#if FT_VERSION == 1
	#define TESTED_NAMESPACE ft
	#include "map.hpp"
	#include "vector.hpp"
	#include "stack.hpp"
#else
	#define TESTED_NAMESPACE std
	#include <map>
	#include <vector>
	#include <stack>
#endif

void	test_vector(void)
{
	TESTED_NAMESPACE::vector<int> vct;
	
	// PUSH_BACK/POP_BACK/FRONT/BACK/EMPTY
	vct.push_back(10);
	vct.push_back(20);
	vct.pop_back();
	vct.pop_back();
	vct.push_back(10);
	vct.push_back(28);

	std::cout << "front: " << vct.front() << ", back: " << vct.back() << std::endl;

	std::cout << "empty: " << vct.empty() << std::endl;

	// CPY CONSTRUCTOR
	TESTED_NAMESPACE::vector<int> vct2(vct);
	
	vct2.push_back(28);
	vct2.push_back(1231232);

	// ITERATOR
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct2.begin();it != vct2.end();++it)
		std::cout << *it << std::endl;

	// REVERSE ITERATOR
	for (TESTED_NAMESPACE::vector<int>::reverse_iterator it = vct2.rbegin();it != vct2.rend();++it)
		std::cout << *it << std::endl;
	
	// RESIZE, RESERVE, SIZE, CAPACITY, MAX_SIZE
	vct.resize(10);

	std::cout << "size: " << vct.size() << ", capacity: " << vct.capacity() << ", max_size" << vct.max_size() << std::endl;

	vct.reserve(100);

	std::cout << "size: " << vct.size() << ", capacity: " << vct.capacity() << ", max_size" << vct.max_size() << std::endl;

	vct.resize(1);

	std::cout << "size: " << vct.size() << ", capacity: " << vct.capacity() << ", max_size" << vct.max_size() << std::endl;

	// ERASE, INSERT
	vct.insert(vct.begin(), vct2.begin(), vct2.end());
	vct.insert(vct.begin(), 1);

	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;

	vct.erase(vct.begin(), vct.begin() + 2);
	
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;
	
	vct.erase(vct.begin(), vct.end() - 1);
	vct.erase(vct.begin());

	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;
	
	vct.insert(vct.begin(), vct2.begin(), vct2.end());
	vct.insert(vct.begin(), vct2.begin(), vct2.end());
	vct.insert(vct.begin(), vct2.begin(), vct2.end());

	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;

	// CLEAR
	vct.clear();

	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;

	vct.insert(vct.begin(), vct2.begin(), vct2.end());
	vct.insert(vct.begin(), vct2.begin(), vct2.end());
	vct.insert(vct.begin(), vct2.begin(), vct2.end());


	// OPERATOR []/AT
	std::cout << vct[0] << ", " << vct[1] << ", " << vct.at(0) << ", " << vct.at(5) << std::endl;


	// COPY
	vct2 = vct;
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct2.begin();it != vct2.end();++it)
		std::cout << *it << std::endl;

	// ASSIGN
	vct2.assign(100, 0);
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct2.begin();it != vct2.end();++it)
		std::cout << *it << std::endl;
	vct.assign(1, 1);
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;

	// SWAP
	vct.swap(vct2);
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct2.begin();it != vct2.end();++it)
		std::cout << *it << std::endl;
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin();it != vct.end();++it)
		std::cout << *it << std::endl;
}

void	print_bounds(TESTED_NAMESPACE::map<int, std::string> m, int key)
{
	TESTED_NAMESPACE::map<int, std::string>::iterator lower_bound = m.lower_bound(key);
	TESTED_NAMESPACE::map<int, std::string>::iterator upper_bound = m.upper_bound(key);
	
	std::cout << "with key: " << key << std::endl;

	if (lower_bound == m.end())
		std::cout << "lower_bound: end()" << std::endl;
	else
		std::cout << "lower_bound: " << lower_bound->first << std::endl;
	if (upper_bound == m.end())
		std::cout << "upper_bound: end()" << std::endl;
	else
		std::cout << "upper_bound: " << lower_bound->first << std::endl;
}

void	print_bounds(TESTED_NAMESPACE::map<std::string, int> m, std::string key)
{
	TESTED_NAMESPACE::map<std::string, int>::iterator lower_bound = m.lower_bound(key);
	TESTED_NAMESPACE::map<std::string, int>::iterator upper_bound = m.upper_bound(key);
	
	std::cout << "with key: " << key << std::endl;

	if (lower_bound == m.end())
		std::cout << "lower_bound: end()" << std::endl;
	else
		std::cout << "lower_bound: " << lower_bound->first << std::endl;
	if (upper_bound == m.end())
		std::cout << "upper_bound: end()" << std::endl;
	else
		std::cout << "upper_bound: " << lower_bound->first << std::endl;
}

void	test_map(void)
{
	TESTED_NAMESPACE::map<int, std::string> map;
	TESTED_NAMESPACE::map<int, std::string> map2;

	// OPERATOR []/AT
	map[0] = "salut";
	map[1] = "salut2";
	map[2] = "la vie est belle";


	std::cout << map[0] << ", " << map.at(1) << std::endl;
	// CPY
	map2 = map;

	// EMPTY, SIZE, MAX_SIZE, CLEAR, CPY
	std::cout << "empty: " << (map.empty()) << ", " << "size: " << map.size() << ", max_size: " << map.max_size() << std::endl;
	map.clear();
	std::cout << "empty: " << (map.empty()) << ", " << "size: " << map.size() << ", max_size: " << map.max_size() << std::endl;
	map = map2;

	// INSERT, ITERATOR
	map.insert(map2.begin(), map2.end());
	for (TESTED_NAMESPACE::map<int, std::string>::iterator it = map.begin();it != map.end();++it)
		std::cout << it->first << ", " << it->second << std::endl;


	// ERASE
	map.erase(map.begin(), ++map.begin());
	for (TESTED_NAMESPACE::map<int, std::string>::iterator it = map.begin();it != map.end();++it)
		std::cout << it->first << ", " << it->second << std::endl;
	map2.erase(map2.begin(), map2.end());
	for (TESTED_NAMESPACE::map<int, std::string>::iterator it = map2.begin();it != map2.end();++it)
		std::cout << it->first << ", " << it->second << std::endl;


	// SWAP
	map2[100] = "value";
	map2.swap(map);
	for (TESTED_NAMESPACE::map<int, std::string>::iterator it = map.begin();it != map.end();++it)
		std::cout << it->first << ", " << it->second << std::endl;
	for (TESTED_NAMESPACE::map<int, std::string>::iterator it = map2.begin();it != map2.end();++it)
		std::cout << it->first << ", " << it->second << std::endl;
	
	// COUNT, FIND, EQUAL_RANGE, LOWER_BOUND, UPPER_BOUND
	std::cout << "count: " << map2.count(100) << ", " << map2.find(100)->second << std::endl;
	std::cout << "empty: " << (map.empty()) << ", " << "size: " << map.size() << ", max_size: " << map.max_size() << std::endl;

	map.swap(map2);
	map[100] = "vvvv";
	for (TESTED_NAMESPACE::map<int, std::string>::iterator it = map.begin();it != map.end();++it)
		std::cout << it->first << ", " << it->second << std::endl;
	print_bounds(map, 100);
	print_bounds(map, 50);
	print_bounds(map, 76);
	
	TESTED_NAMESPACE::map<std::string, int> mp;

	mp.insert(TESTED_NAMESPACE::pair<std::string, int>("ft", 42));
	mp.insert(TESTED_NAMESPACE::pair<std::string, int>("one", 1));
	print_bounds(mp, "zaa");
}

void	test_stack(void)
{
	TESTED_NAMESPACE::stack<int> stack;

	// PUSH, POP
	stack.push(10);
	stack.push(27);
	stack.push(30);
	stack.pop();
	stack.pop();
	stack.push(28);
	stack.push(954);

	// CPY
	TESTED_NAMESPACE::stack<int> stack2(stack);

	// TOP
	std::cout << stack.top() << std::endl;
	std::cout << stack2.top() << std::endl;

	// SIZE, EMPTY
	std::cout << ", " << stack.size() << ", " << stack.empty() << std::endl;
}

int main(void)
{
	test_vector();
	test_map();
	return (0);
}
