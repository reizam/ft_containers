/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:47:31 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/23 06:42:09 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef FT_VERSION
# define FT_VERSION 1
#endif

#if FT_VERSION == 1
#define TESTED_NAMESPACE ft
# include "vector.hpp"
# include "iterator.hpp"
# include <algorithm>
#else
# include <vector>
# include <iterator>
#define TESTED_NAMESPACE std
#endif

#define TESTED_TYPE int

#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

#include <list>
#include <iostream>


void	test_vector()
{
	TESTED_NAMESPACE::vector<int> vector;
	TESTED_NAMESPACE::vector<int> vector2(2);

	vector.push_back(2);
	vector.push_back(2);
	vector.erase(vector.begin(), vector.end());
	vector.push_back(5);
	vector.push_back(7);
	vector.push_back(7);
	vector.push_back(7);
	vector.push_back(-5);
	vector.insert(vector.begin(), 2, 5);
	vector.pop_back();
	vector.resize((size_t)10);
	vector.reserve(100);
	vector.erase(vector.begin() + 2, vector.end() - 1);
	vector.assign(1000, 0);

	
	std::cout << "empty: " << (vector.empty() ? "yes" : "no") << std::endl;
	std::cout << "size: " <<  vector.size() << std::endl;
	std::cout << "max_size: " << vector.max_size() << std::endl; 
	std::cout << "capacity: " << vector.capacity() << std::endl;
	std::cout << "front: " << vector.front() << std::endl;
	std::cout << "back: " << vector.back() << std::endl;

	std::cout << "------ CONTENT -------" << std::endl;

	TESTED_NAMESPACE::vector<int>::iterator it = vector.begin();
	TESTED_NAMESPACE::vector<int>::iterator ite = vector.end();

	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}	
}


int		main(void)
{
	test_vector();
	return (0);
}