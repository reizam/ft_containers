/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:36:17 by kmazier           #+#    #+#             */
/*   Updated: 2021/12/01 16:01:02 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <memory>
#include "common.hpp"
#include "vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container 							container_type;
			typedef typename Container::value_type 		value_type;
			typedef typename Container::size_type 		size_type;
			typedef typename Container::reference 		reference;
			typedef typename Container::const_reference	const_reference;
		public:
			// MEMBERS FUNCTIONS
			explicit stack(const Container& cont = Container()) : c(cont) {}
			
			stack(const stack& other)
			{
				*this = other;
			}

			~stack() {}

			stack&	operator=(const stack& other)
			{
				if (*this != other)
					this->c = other.c;
				return (*this);
			}

			// ELEMENT ACCESS
			reference			top()
			{
				return (this->c.back());
			}

			const_reference 	top() const
			{
				return (this->c.back());
			}

			// CAPACITY
			bool				empty() const
			{
				return (this->c.empty());
			}

			size_type			size() const
			{
				return (this->c.size());
			}

			// MODIFIERS
			void				push(const value_type& value)
			{
				this->c.push_back(value);
			}

			void				pop()
			{
				this->c.pop_back();
			}
		public:
			container_type c;
	};
	
	template<class T, class Container>
	bool	operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	
	template<class T, class Container>
	bool	operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	}

	template<class T, class Container>
	bool	operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template<class T, class Container>
	bool	operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template<class T, class Container>
	bool	operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template<class T, class Container>
	bool	operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif