/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:38:23 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/26 09:47:31 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VERSION
# define FT_VERSION 1
#endif

#if FT_VERSION == 1
#define TESTED_NAMESPACE ft
# include "vector.hpp"
# include "iterator.hpp"
#else
# include <vector>
# include <iterator>
#define TESTED_NAMESPACE std
#endif


#include <iostream>

int main(void)
{
	TESTED_NAMESPACE::vector<int> vct;

	vct.push_back(1);
	vct.push_back(2);
	vct.push_back(3);
	
	vct.insert(vct.begin() + 1, 100);
	vct.insert(vct.begin(), vct.begin(), vct.end());
	for (TESTED_NAMESPACE::vector<int>::iterator it = vct.begin(); it != vct.end();++it)
		std::cout << *it << std::endl;
}