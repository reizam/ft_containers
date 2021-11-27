/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 07:15:21 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/27 05:37:38 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_COMMON_HPP
# define FT_CONTAINERS_COMMON_HPP

#include "iterator.hpp"

namespace ft
{
	
	template<class T>
	T* addressof(T& arg)
	{
		return &arg;
	}

	template<class InputIt, class NoThrowForwardIt>
	NoThrowForwardIt uninitialized_copy(InputIt first, InputIt last, NoThrowForwardIt d_first)
	{
		typedef typename ft::iterator_traits<NoThrowForwardIt>::value_type T;
		NoThrowForwardIt current = d_first;
		try {
			for (; first != last; ++first, (void) ++current) {
				::new (const_cast<void*>(static_cast<const volatile void*>(
					addressof(*current)))) T(*first);
			}
			return current;
		} catch (...) {
			for (; d_first != current; ++d_first) {
				d_first->~T();
			}
			throw;
		}
	}
	
	template<typename T>
	void	swap(T *a, T *b)
	{
		T tmp;
		
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	
	template<typename T1, typename T2, typename Result>
    struct binary_function
    {
      typedef T1 		first_argument_type; 

      typedef T2 		second_argument_type;

      typedef Result 	result_type;
    };

	template<typename Arg, typename Result>
    struct unary_function
    {
      	typedef Arg		argument_type;   

     	 typedef Result	result_type;  
    };

	template<typename T>
    struct less : public binary_function<T, T, bool>
    {
      	bool operator()(const T& x, const T& y) const
     	{
			return x < y;
		}
    };
};


#endif