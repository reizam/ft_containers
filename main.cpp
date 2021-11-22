/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:47:31 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/22 02:23:46 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef FT_VERSION
# define FT_VERSION 1
#endif

#if FT_VERSION == 1
#define NAMESPACE ft
# include "vector.hpp"
# include "iterator.hpp"
#else
# include <vector>
# include <iterator>
#define NAMESPACE std
#endif

int main(void)
{
	if (FT_VERSION == 1)
		std::cout << "FT_VERSION:" << std::endl;
	else
		std::cout << "STD_VERSION:" << std::endl;

	NAMESPACE::vector<int> vector;

	vector.push_back(2);
	vector.push_back(5);
	vector.push_back(7);
	vector.push_back(-5);


	std::cout << "empty: " << (vector.empty() ? "yes" : "no") << std::endl;
	std::cout << "size: " <<  vector.size() << std::endl;
	std::cout << "max_size: " << vector.max_size() << std::endl; 
	std::cout << "capacity: " << vector.capacity() << std::endl;
	std::cout << "front: " << vector.front() << std::endl;
	std::cout << "back: " << vector.back() << std::endl;

	std::cout << "------ CONTENT -------" << std::endl;

	NAMESPACE::vector<int>::iterator it = vector.begin();
	NAMESPACE::vector<int>::iterator ite = vector.end();

	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}	
}

// int main()
// {
// 	std::vector<int> vector;
// 	std::vector<int> vector2;

// 	vector.push_back(2);
// 	vector.push_back(100);
// 	vector.push_back(120);
// 	vector.push_back(130);
// 	vector.push_back(140);
// 	vector.push_back(150);
// 	vector.push_back(160);
// 	vector.push_back(170);

// 	vector2.push_back(10);
// 	vector2.push_back(10);
// 	vector2.push_back(10);
// 	vector2.push_back(10);
// 	vector2.push_back(10);
// 	vector2.push_back(10);
// 	vector2.push_back(10);
// 	vector2.push_back(10);
// 	vector2.push_back(10);
	
// 	std::cout << "----- size: " << vector.size() << " capacity: " << vector.capacity() << std::endl;

// 	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
//        std::cout << *it << std::endl;
//     }

// 	vector.erase(vector2.begin(), vector2.begin() + 5);

// 	std::cout << "----- size: " << vector.size() << " capacity: " << vector.capacity() << std::endl;

// 	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
//        std::cout << *it << std::endl;
//     }

// 	vector.erase(vector.begin());
	
// 	std::cout << "----- size: " << vector.size() << " capacity: " << vector.capacity() << std::endl;

// 	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
//        std::cout << *it << std::endl;
//     }
// }