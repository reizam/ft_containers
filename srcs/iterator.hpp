/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:15:38 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/25 06:36:37 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <cstddef>
#include "type_traits.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
  	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	

	template<typename Category, typename T, typename Distance =  ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	struct iterator
	{
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	};

	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	template<typename Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
											 typename iterator_traits<Iterator>::value_type,
											 typename iterator_traits<Iterator>::difference_type,
											 typename iterator_traits<Iterator>::pointer,
											 typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator current;

			typedef iterator_traits<Iterator>	traits_type;
		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;

			reverse_iterator(void) : current() {}

			explicit reverse_iterator(iterator_type x) : current(x) {}
			
			template<typename U>
			reverse_iterator(const reverse_iterator<U> &other) : current(other.base()) {}

			iterator_type base(void) const
			{
				return (this->current);
			}

			reference	operator*(void) const
			{
				Iterator tmp = current;
				return (*--tmp);
			}

			pointer operator->() const
     		{
				 return (&(operator*()));
			}

			reverse_iterator&	operator++()
			{
				--this->current;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				return reverse_iterator(current--);
			}

			reverse_iterator&	operator--()
			{
				++this->current;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				return (reverse_iterator(current++));
			}

			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}

			reverse_iterator&	operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(current + n));
			}

			reverse_iterator&	operator-=(difference_type n)
			{
				current += n;
				return (*this); 
			}

			reference			operator[](difference_type n) const
			{
				return (*(*this + n));
			}
	};

	using ft::iterator_traits;
 	using ft::iterator;
	template<typename Iterator, typename Container>
	class	normal_iterator 
	{
		protected:
			Iterator current;

			typedef iterator_traits<Iterator>	traits_type;
		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;

		normal_iterator() : current(Iterator()) {}
		
		template<typename Iter>
        normal_iterator(const normal_iterator<Iter, Container> &i) : current(i.base()) {}

		normal_iterator(const Iterator& i) : current(i) {}
		
		reference	operator*() const
		{
			return (*current);
		}

		pointer	operator->() const
		{
			return (current);
		}

		normal_iterator& operator++()
		{
			++current;
			return (*this);
		}

		normal_iterator	operator++(int)
		{
			return (normal_iterator(current++));
		}

		normal_iterator&	operator--()
		{
			--current;
			return (*this);
		}

		normal_iterator operator--(int)
		{
			return (normal_iterator(current--));
		}

		reference	operator[](difference_type n) const
		{
			return *(current + n);
		}

		normal_iterator&	operator+=(difference_type n)
		{
			current += n;
			return (*this);
		}

		normal_iterator	operator+(difference_type n) const
		{
			return (normal_iterator(current + n));
		}

		normal_iterator&	operator-=(difference_type n)
		{
			current -= n;
			return (*this);
		}

		normal_iterator	operator-(difference_type n) const
		{
			return (normal_iterator(current - n));
		}

		const Iterator&	base() const
		{
			return (current);
		}
	};

	template<typename Iterator>
	inline bool	operator==(const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b)
	{
		return (a.base() == b.base());
	}

	template<typename Iterator>
	inline bool	operator!=(const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b)
	{
		return (a.base() != b.base());
	}

	template<typename Iterator>
	inline bool	operator>=(const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b)
	{
		return (a.base() >= b.base());
	}

	template<typename Iterator>
	inline bool	operator<=(const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b)
	{
		return (a.base() <= b.base());
	}

	template<typename Iterator>
	inline bool	operator>(const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b)
	{
		return (a.base() > b.base());
	}

	template<typename Iterator>
	inline bool	operator<(const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b)
	{
		return (a.base() < b.base());
	}

	template<typename Iterator_A, typename Iterator_B>
	inline bool	operator==(const reverse_iterator<Iterator_A>& a, const reverse_iterator<Iterator_B>& b)
	{
		return (a.base() == b.base());
	}

	template<typename Iterator_A, typename Iterator_B>
	inline bool	operator!=(const reverse_iterator<Iterator_A>& a, const reverse_iterator<Iterator_B>& b)
	{
		return (a.base() != b.base());
	}

	template<typename Iterator_A, typename Iterator_B>
	inline bool	operator>=(const reverse_iterator<Iterator_A>& a, const reverse_iterator<Iterator_B>& b)
	{
		return (a.base() >= b.base());
	}

	template<typename Iterator_A, typename Iterator_B>
	inline bool	operator<=(const reverse_iterator<Iterator_A>& a, const reverse_iterator<Iterator_B>& b)
	{
		return (a.base() <= b.base());
	}

	template<typename Iterator_A, typename Iterator_B>
	inline bool	operator>(const reverse_iterator<Iterator_A>& a, const reverse_iterator<Iterator_B>& b)
	{
		return (a.base() > b.base());
	}

	template<typename Iterator_A, typename Iterator_B>
	inline bool	operator<(const reverse_iterator<Iterator_A>& a, const reverse_iterator<Iterator_B>& b)
	{
		return (a.base() < b.base());
	}

	template<typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b)
	{
		return (b.base() - a.base());
	}

	template<typename Iterator_A, typename Iterator_B>
	inline typename reverse_iterator<Iterator_A>::difference_type operator-(const reverse_iterator<Iterator_A>& a, const reverse_iterator<Iterator_B>& b)
	{
		return (b.base() - a.base());
	}

	template<typename Iterator>
	inline reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& a)
	{
		return reverse_iterator<Iterator>(a.base() - n);
	}

	template<typename Iterator, typename Container>
	inline bool	operator==(const normal_iterator<Iterator, Container>& a, const normal_iterator<Iterator, Container>& b)
	{
		return (a.base() == b.base());
	}

	template<typename Iterator, typename Container>
	inline bool	operator!=(const normal_iterator<Iterator, Container>& a, const normal_iterator<Iterator, Container>& b)
	{
		return (a.base() != b.base());
	}

	template<typename Iterator, typename Container>
	inline bool	operator>=(const normal_iterator<Iterator, Container>& a, const normal_iterator<Iterator, Container>& b)
	{
		return (a.base() >= b.base());
	}

	template<typename Iterator, typename Container>
	inline bool	operator<=(const normal_iterator<Iterator, Container>& a, const normal_iterator<Iterator, Container>& b)
	{
		return (a.base() <= b.base());
	}

	template<typename Iterator, typename Container>
	inline bool	operator>(const normal_iterator<Iterator, Container>& a, const normal_iterator<Iterator, Container>& b)
	{
		return (a.base() > b.base());
	}

	template<typename Iterator, typename Container>
	inline bool	operator<(const normal_iterator<Iterator, Container>& a, const normal_iterator<Iterator, Container>& b)
	{
		return (a.base() < b.base());
	}

	template<typename Iterator_A, typename Iterator_B, typename Container>
	inline bool	operator==(const normal_iterator<Iterator_A, Container>& a, const normal_iterator<Iterator_B, Container>& b)
	{
		return (a.base() == b.base());
	}

	template<typename Iterator_A, typename Iterator_B, typename Container>
	inline bool	operator!=(const normal_iterator<Iterator_A, Container>& a, const normal_iterator<Iterator_B, Container>& b)
	{
		return (a.base() != b.base());
	}

	template<typename Iterator_A, typename Iterator_B, typename Container>
	inline bool	operator>=(const normal_iterator<Iterator_A, Container>& a, const normal_iterator<Iterator_B, Container>& b)
	{
		return (a.base() >= b.base());
	}

	template<typename Iterator_A, typename Iterator_B, typename Container>
	inline bool	operator<=(const normal_iterator<Iterator_A, Container>& a, const normal_iterator<Iterator_B, Container>& b)
	{
		return (a.base() <= b.base());
	}

	template<typename Iterator_A, typename Iterator_B, typename Container>
	inline bool	operator>(const normal_iterator<Iterator_A, Container>& a, const normal_iterator<Iterator_B, Container>& b)
	{
		return (a.base() > b.base());
	}

	template<typename Iterator_A, typename Iterator_B, typename Container>
	inline bool	operator<(const normal_iterator<Iterator_A, Container>& a, const normal_iterator<Iterator_B, Container>& b)
	{
		return (a.base() < b.base());
	}

	template<typename Iterator, typename Container>
	inline typename normal_iterator<Iterator, Container>::difference_type operator-(const normal_iterator<Iterator, Container>& a, const normal_iterator<Iterator, Container>& b)
	{
		return (a.base() - b.base());
	}

	template<typename Iterator_A, typename Iterator_B, typename Container>
	inline typename normal_iterator<Iterator_A, Container>::difference_type operator-(const normal_iterator<Iterator_A, Container>& a, const normal_iterator<Iterator_B, Container>& b)
	{
		return (a.base() - b.base());
	}

	template<typename Iterator, typename Container>
	inline normal_iterator<Iterator, Container>	operator+(typename normal_iterator<Iterator, Container>::difference_type n, const normal_iterator<Iterator, Container>& a)
	{
		return normal_iterator<Iterator, Container>(a.base() + n);
	}
};


#endif