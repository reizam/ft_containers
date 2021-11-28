/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 08:46:52 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/28 04:07:45 by kmazier          ###   ########.fr       */
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
int main(void)
{
	ft::map<int, std::string> map;

	map.insert(ft::make_pair<int, std::string>(10, "pomme dans la fraise"));
}