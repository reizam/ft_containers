/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 08:46:52 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/28 11:59:52 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "tree.hpp"
// #include "pair.hpp"
// #include "common.hpp"
// #include <iostream>
// #include <memory>

#include "map.hpp"
#include <iostream>
#include "avltree.hpp"
#include "pair.hpp"

int main(void)
{
	ft::map<int, std::string> map;

	map.insert(ft::make_pair<const int, std::string>(9, "pomme de la vie"));
	map.insert(ft::make_pair<const int, std::string>(5, "fraise"));
	map.insert(ft::make_pair<const int, std::string>(11, "orange"));
	map.insert(ft::make_pair<const int, std::string>(12, "orange deluxe mamene"));
	map.insert(ft::make_pair<const int, std::string>(13, "orange"));
	map.insert(ft::make_pair<const int, std::string>(14, "orange"));
	map.insert(ft::make_pair<const int, std::string>(15, "orange"));
	
	map.clear();

	map.insert(ft::make_pair<const int, std::string>(9, "pomme de la vie"));
}