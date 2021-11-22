/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:43:47 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/22 03:08:44 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include "iterator.hpp"

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class	vector
	{
		public:
			typedef T													value_type;
			typedef typename Allocator::template rebind<T>::other		allocator_type;
			typedef size_t												size_type;
			typedef __gnu_cxx::ptrdiff_t								difference_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::normal_iterator<pointer, vector> 				iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
		public:
			// MEMBER FUNCTIONS
			vector(void) :  start(), finish(), end_of_storage(), allocator() {}

			explicit vector(const Allocator &_allocator) : start(), finish(), end_of_storage(), allocator(_allocator) {}
			
			explicit vector(size_type size, const T &value = T(), const Allocator &_allocator = Allocator()) : allocator(_allocator)
			{
				this->fill_initialize(size, value);
			}

			template<class InputIt>
			vector(InputIt first, InputIt last, const Allocator &_allocator) : allocator(_allocator)
			{
				this->fill_initialize(first, last);
			}

			~vector(void)
			{
				this->delete_storage();
			}

			allocator_type	get_allocator_type(void) const
			{
				return (this->allocator);
			}

			vector	&		operator=(const vector &other)
			{
				// COPY
				(void)other;
				return (*this);
			}

			// ELEMENT ACCESS
			reference			operator[](size_type index)
			{
				return (*(this->start + index));
			}

			const_reference			operator[](size_type index) const
			{
				return (*(this->start + index));
			}
			
			reference			at(size_type index)
			{
				if (index >= this->size())
					throw std::out_of_range("vector: out of range");
				return ((*this)[index]);
			}

			const_reference		at(size_type index) const
			{
				if (index >= this->finish - this->start)
					throw std::out_of_range("vector: out of range");
				return ((*this)[index]);
			}

			reference			front(void)
			{
				return (*(this->begin()));
			}

			const_reference		front(void) const
			{
				return (*(this->begin()));
			}

			reference			back(void)
			{
				return (*(this->end() - 1));
			}

			const_reference		back(void) const
			{
				return (*(this->end() - 1));
			}

			pointer					data(void)
			{
				return (this->empty() ? NULL : this->start);
			}

			const pointer			data(void) const
			{
				return (this->empty() ? NULL : this->start);
			}

			// ITERATORS
			iterator 			begin()
			{
				return iterator(this->start);
			}

			iterator 			end()
			{
				return iterator(this->finish);
			}

			reverse_iterator 	rbegin() 
			{
				return reverse_iterator(end());
			}

			reverse_iterator 	rend() 
			{
				return reverse_iterator(begin());
			}

			// CAPACITY
			bool				empty(void) const
			{
				return (this->finish - this->start == 0);
			}

			size_type			size(void) const
			{	
				return (this->finish - this->start);
			}

			size_type			max_size(void) const
			{
				return (this->allocator.max_size());
			}

			void	reserve(size_type new_cap)
			{
				if (new_cap > this->max_size())
					throw std::length_error("vector: length error");
				if (capacity() < new_cap)
					reallocate(new_cap);
			}

			size_type			capacity(void) const
			{
				return (size_type(this->end_of_storage - this->start));
			}

			// MODIFIERS
			void				clear(void)
			{
				this->allocator.destroy(this->start);
				this->finish = this->start;
			}

			iterator			insert(iterator pos, const T &value)
			{
				size_type diff = pos - this->begin();

				this->insert_value(diff, value);
				return (this->begin() + diff);
			}

			void				insert(iterator pos, size_type amount, const T &value )
			{
				size_type diff = pos - this->begin();

				this->insert_fill_value(diff, amount, value);
			}

			template<class InputIt>
			void				insert(iterator pos, InputIt first, InputIt last)
			{
				size_type diff = pos - this->begin();
				
				this->insert_iterator(diff, first, last);
			}

			iterator			erase(iterator pos)
			{
				size_type diff = pos - this->begin();

				this->erase_value(diff);
				return (this->begin() + diff);
			}

			iterator			erase(iterator first, iterator last)
			{
				return (this->erase_iterator_value(first, last));
			}

			void				push_back(const T &value)
			{
				if (this->finish == this->end_of_storage)
					this->reallocate(this->size() + 1);
				this->allocator.construct(this->finish, value);
				++this->finish;
			}

			void				pop_back(void)
			{
				if (this->size() > 0)
					this->erase_value(this->size() - 1);
			}

			void				resize(size_type count)
			{
				if (this->size() < count)
					this->reallocate(count);
				else
					this->reallocate(count);
			}

			void			resize(size_type count, T value = T() )
			{
				if (this->size() < count)
					this->reallocate(count);
				else
					this->reallocate_fill(count, value);
			}

			void			swap(vector &other)
			{
				this->swap_vector(other);
			}

		private:
			pointer			start;
			pointer 		finish;
			pointer 		end_of_storage;
			allocator_type	allocator;

			void	create_storage(size_type size)
			{
				this->start = this->allocator.allocate(size);
				this->finish = this->start;
				this->end_of_storage = this->start + size;
			}

			void	delete_storage(void)
			{
				this->allocator.destroy(start);
				this->allocator.deallocate(start, this->size());
			}

			void	fill_initialize(size_type size, value_type &value)
			{
				this->create_storage(size);
				for (size_type i = 0;i < size;i++)
					this->allocator.construct(this->finish++, value);
			}
			
			void	swap_pointer(pointer a, pointer b)
			{
				pointer tmp;

				tmp = a;
				a = b;
				b = tmp;
			}

			void	swap_vector(vector &other)
			{
				swap_pointer(other.start, this->start);
				swap_pointer(other.finish, this->finish);
				swap_pointer(other.end_of_storage, this->end_of_storage);
			}

			template<class InputIt>
			void	fill_initialize(InputIt first, InputIt last)
			{
				this->create_storage(last - first);
				for (InputIt it = first;it != last;it++)
					this->allocator.construct(this->finish++, *it);
			}

			void	reallocate(size_type size)
			{
				size_type		before_size = this->size();
				pointer 		_start 		= this->allocator.allocate(size);
				pointer 		_finish		= _start;

				for (size_type i = 0;i < before_size;i++)
				{
					this->allocator.construct(_finish, *(this->start + i));
					++_finish;
				}
				this->delete_storage();
				this->start = _start;
				this->finish = _finish;
				this->end_of_storage = _start + size;
			}

			void	reallocate(size_type size, T value)
			{
				pointer _start = this->allocator.allocate(size);
				pointer _finish = _start;

				for (size_type i = 0;i < size;i++)
				{
					if (_finish)
						this->allocator.construct(_finish, *this[i]);
					else
						this->allocator.construct(_finish, value);
					++_finish;
				}
				this->delete_storage();
				this->start = _start;
				this->finish = _finish;
				this->end_of_storage = _start + size;
			}

			void	insert_value(size_type pos, const_reference value)
			{
				value_type	tmp;
				value_type	tmp2;

				if (this->finish == this->end_of_storage)
					this->reallocate(this->size() + 1);
				tmp = *(this->start + pos);
				this->allocator.construct(this->start + pos, value);
				for (size_type i = pos + 1;i < this->size() + 1;i++)
				{
					tmp2 = *(this->start + i);
					this->allocator.construct(this->start + i, tmp);
					tmp = tmp2;
				}
				++this->finish;
			}

			void	insert_fill_value(size_type pos, size_type amount, const_reference value)
			{
				if (amount == 0) return ;
				if (capacity() - size() < amount)
					this->reallocate(this->size() + amount);
				for (size_type i = 0;i < amount;i++)
					this->insert_value(pos, value);
			}

			template<class InputIt>
			void	insert_iterator(size_type pos, InputIt first, InputIt last)
			{
				size_type range_size = last - first;

				if (range_size == 0) return ;
				if (capacity() - size() < range_size)
					this->reallocate(this->size() + range_size);
				for (InputIt it = first;it != last;++it)
					this->insert_value(pos, *it);
			}

			void	erase_value(size_type pos)
			{
				this->allocator.destroy(this->start + pos);
				for (size_type i = pos;i < this->size() - 1;i++)
					this->allocator.construct(this->start + i, *(this->start + i + 1));
				this->allocator.destroy(this->finish);
				--this->finish;
			}

			iterator	erase_iterator_value(iterator first, iterator last)
			{
				size_type start = first - this->begin();
				size_type end = last - this->begin();

				if (first - last == 0)
					return (last);
				for (size_type i = start;i < end;i++)
					this->erase_value(start);
				return (this->begin() + start);
			}
	};
}


#endif