/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:47:31 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/24 09:46:58 by kmazier          ###   ########.fr       */
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


// void	test_vector()
// {
// 	TESTED_NAMESPACE::vector<int> vector;
// 	TESTED_NAMESPACE::vector<int> vector2(2);

// 	vector.push_back(2);
// 	vector.push_back(2);
// 	vector.erase(vector.begin(), vector.end());
// 	vector.push_back(5);
// 	vector.push_back(7);
// 	vector.push_back(7);
// 	vector.push_back(7);
// 	vector.push_back(-5);
// 	vector.insert(vector.begin(), 2, 5);
// 	vector.pop_back();
// 	vector.resize((size_t)10);
// 	vector.reserve(100);
// 	vector.erase(vector.begin() + 2, vector.end() - 1);
// 	vector.assign(1000, 0);

	
// 	std::cout << "empty: " << (vector.empty() ? "yes" : "no") << std::endl;
// 	std::cout << "size: " <<  vector.size() << std::endl;
// 	std::cout << "max_size: " << vector.max_size() << std::endl; 
// 	std::cout << "capacity: " << vector.capacity() << std::endl;
// 	std::cout << "front: " << vector.front() << std::endl;
// 	std::cout << "back: " << vector.back() << std::endl;

// 	std::cout << "------ CONTENT -------" << std::endl;

// 	TESTED_NAMESPACE::vector<int>::iterator it = vector.begin();
// 	TESTED_NAMESPACE::vector<int>::iterator ite = vector.end();

// 	while (it != ite)
// 	{
// 		std::cout << *it << std::endl;
// 		it++;
// 	}	
// }

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void	checkErase(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct,
					TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

void	prepost_incdec(TESTED_NAMESPACE::vector<TESTED_TYPE> &vct)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}

void	test(void)
{
	std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
	printSize(vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	printSize(vct);

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	printSize(vct);
}

int		main(void)
{
	
	return (0);
}