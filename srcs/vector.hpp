/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 06:19:28 by kmazier           #+#    #+#             */
/*   Updated: 2021/12/01 15:00:30 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "common.hpp"

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
			typedef ft::normal_iterator<const_pointer, vector>			const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		public:
			// MEMBER FUNCTIONS
			vector(void) :  start(), finish(), end_of_storage(), allocator() {}

			explicit vector(const Allocator &_allocator) : start(), finish(), end_of_storage(), allocator(_allocator) {}
			
			explicit vector(size_type size, const T &value = T(), const Allocator &_allocator = Allocator()) : allocator(_allocator)
			{
				this->create_storage(size, value, true_type());
			}

			template<class InputIt>
			vector(InputIt first, InputIt last, const Allocator &_allocator = Allocator()) : allocator(_allocator)
			{
				typedef typename ft::is_integral<InputIt>::type integral;

				this->create_storage(first, last, integral());
			}

			vector(const vector& other) : allocator()
			{
				if (*this != other)
					this->copy_init(other);
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
				if (*this != other)
					this->copy(other);
				return (*this);
			}

			void			assign(size_type count, const_reference value) 
			{
				this->assign_dispatch(count, value, true_type());
			}

			template<class InputIt>
			void			assign(InputIt first, InputIt last)
			{
				typedef typename ft::is_integral<InputIt>::type integral;
				
				this->assign_dispatch(first, last, integral());
			}

			// ITERATORS
			iterator 			begin()
			{
				return iterator(this->start);
			}

			const_iterator		begin() const
			{
				return const_iterator(this->start);
			}
			
			iterator 			end()
			{
				return iterator(this->finish);
			}

			const_iterator		end() const
			{
				return const_iterator(this->finish);
			}
			
			reverse_iterator		rend()
			{
				return reverse_iterator(begin());
			}
			
			const_reverse_iterator 	rend() const
			{
				return const_reverse_iterator(begin());
			}

			reverse_iterator 	rbegin() 
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator 	rbegin() const
			{
				return const_reverse_iterator(end());
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
					throw std::length_error("vector::reserve");
				if (capacity() < new_cap)
					this->realloc_reserve(new_cap);
			}

			size_type			capacity(void) const
			{
				return (size_type(this->end_of_storage - this->start));
			}
			
			// ELEMENT ACCESS
			reference			operator[](size_type index)
			{
				return (*(this->start + index));
			}

			const_reference		operator[](size_type index) const
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
				if (index >= this->size())
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

			// MODIFIERS
			void				clear(void)
			{
				if (this->size() == 0) return ;

				this->erase_at_end(this->start);								
			}

			void				push_back(const_reference value)
			{
				if (this->finish != this->end_of_storage)
				{
					this->allocator.construct(this->finish, value);
					this->finish++;
				}
				else
					this->realloc_insert(end(), value);
			}

			void				pop_back()
			{
				--this->finish;
				this->allocator.destroy(this->finish);
			}

			iterator			insert(iterator pos, const T &value)
			{
				return (this->realloc_insert(pos, value));
			}

			void				insert(iterator pos, size_type amount, const_reference value)
			{
				this->insert_dispatch(pos, amount, value, true_type());
			}

			template<class InputIt>
			void				insert(iterator pos, InputIt first, InputIt last)
			{
				typedef typename ft::is_integral<InputIt>::type integral;

				this->insert_dispatch(pos, first, last, integral());	
			}

			iterator			erase(iterator pos)
			{
				return (this->_erase(pos));
			}

			iterator			erase(iterator first, iterator last)
			{
				return (this->_erase_range(first, last));
			}

			void			resize(size_type count, value_type value = value_type())
			{
				if (count < this->size())
					this->erase_at_end(&*(this->begin() + count));
				else if (count > this->size())
					this->realloc_resize_fill(count, value);
			}

			void			swap(vector &other)
			{
				if (*this != other)
					this->_swap(other);
			}
			private:
				pointer 		start;
				pointer			finish;
				pointer 		end_of_storage;
				allocator_type	allocator;

				
				void	create_storage(size_type size)
				{
					this->start = this->allocator.allocate(size);
					this->finish = this->start;
					this->end_of_storage = this->start + size;
				}
				
				void	copy_init(const vector &other)
				{
					this->create_storage(other.size());
					for (size_type i = 0;i < other.size();i++)
						this->allocator.construct(this->finish++, other[i]);
				}

				void	copy(const vector &other)
				{
					pointer 	_start(this->allocator.allocate(other.size()));
					pointer 	_finish(_start);

					_finish = pointer();
					_finish = ft::uninitialized_copy(other.begin(), other.end(), _start);
					this->destroy_it(this->start, this->finish);
					this->deallocate(this->start, this->end_of_storage - this->start);
					this->start = _start;
					this->finish = _finish;
					this->end_of_storage = _finish;
				}
				
				void	create_storage(size_type size, value_type value, true_type)
				{
					this->start = this->allocator.allocate(size);
					for (size_type i = 0;i < size;i++)
						this->allocator.construct(this->start + i, value);
					this->finish = this->start + size;
					this->end_of_storage = this->start + size;
				}

				template<class InputIt>
				void	create_storage(InputIt first, InputIt last, false_type)
				{
					this->create_storage(ft::iter_size(first, last));
					for (InputIt it = first;it != last;it++)
						this->allocator.construct(this->finish++, *it);
				}

				void	delete_storage()
				{
					this->destroy_it(this->start, this->finish);
					this->deallocate(this->start, this->end_of_storage - this->start);
				}

				void	deallocate(pointer p, size_t size)
				{
					if (p)
						this->allocator.deallocate(p, size);
				}

				void	erase_at_end(pointer pos)
				{
					this->destroy_it(pos, this->finish);
					this->finish = pos;
				}

				size_t	new_size()
				{
					size_t size = this->size();

					return (size == 0 ? 1 : size * 2);
				}

				size_t	new_size(size_t n)
				{
					size_t size = this->size();
					
					if (this->capacity() >= n)
						return (this->capacity());
					return (n < size * 2 ? size * 2 : n);
				}

				void	realloc_reserve(size_type count)
				{
					pointer		_start(this->allocator.allocate(count));
					pointer		_finish(_start);

					_finish = pointer();
					_finish = ft::uninitialized_copy(this->start, this->finish, _start);
					this->destroy_it(this->start, this->finish);
					this->deallocate(this->start, this->end_of_storage - this->start);
					this->start = _start;
					this->finish = _finish;
					this->end_of_storage = _start + count;
				}

				iterator	realloc_insert(iterator pos, const_reference value)
				{
					size_type	size = new_size();
					size_type	_pos = pos - this->begin();
					pointer		_start(this->allocator.allocate(size));
					pointer		_finish(_start);

					this->allocator.construct(_start + _pos, value);
					_finish = pointer();
					_finish = ft::uninitialized_copy(this->start, pos.base(), _start);
					++_finish;
					_finish = ft::uninitialized_copy(pos.base(), this->finish, _finish);
					this->destroy_it(this->start, this->finish);
					this->deallocate(this->start, this->end_of_storage - this->start);
					this->start = _start;
					this->finish = _finish;
					this->end_of_storage = _start + size;
					return (this->begin() + _pos);
				}

				template<class InputIt>
				void	insert_dispatch(iterator pos, InputIt first, InputIt last, false_type)
				{
					this->realloc_insert_range(pos, first, last);
				}

				void	insert_dispatch(iterator pos, size_type count, const_reference value, true_type)
				{
					this->realloc_insert_fill(pos, count, value);
				}

				void	assign_dispatch(size_type count, const_reference value, true_type)
				{
					this->assign_fill(count, value);
				}

				template<class InputIt>
				void	assign_dispatch(InputIt first, InputIt last, false_type)
				{
					this->assign_range(first, last);
				}

				template<class InputIt>
				void	realloc_insert_range(iterator pos, InputIt first, InputIt last)
				{
					if (first == last) return ;

					difference_type	diff = ft::iter_size(first, last);
					size_type		size = new_size(diff + this->size());
					pointer			_start(this->allocator.allocate(size));
					pointer			_finish(_start);
					
					_finish = pointer();
					_finish = ft::uninitialized_copy(this->start, pos.base(), _start);
					for (; first != last;++first)
						this->allocator.construct(_finish++, *first);
					_finish = ft::uninitialized_copy(pos.base(), this->finish, _finish);
					this->destroy_it(this->start, this->finish);
					this->deallocate(this->start, this->end_of_storage - this->start);
					this->start = _start;
					this->finish = _finish;
					this->end_of_storage = _start + size;
				}

				void	realloc_insert_fill(iterator pos, size_type count, const_reference value)
				{
					if (count == 0) return ;
					
					size_type	_pos = pos - this->begin();
					size_type	size = new_size(count + this->size());
					pointer		_start(this->allocator.allocate(size));
					pointer		_finish(_start);

					for (size_type i = 0;i < count;i++)
						this->allocator.construct(_start + _pos + i, value);
					_finish = pointer();
					_finish = ft::uninitialized_copy(this->start, pos.base(), _start);
					_finish += count;
					_finish = ft::uninitialized_copy(pos.base(), this->finish, _finish);
					this->destroy_it(this->start, this->finish);
					this->deallocate(this->start, this->end_of_storage - this->start);
					this->start = _start;
					this->finish = _finish;
					this->end_of_storage = _start + size;
				}

				void	realloc_resize_fill(size_type count, const_reference value)
				{
					if (count == 0) return ;
					
					size_type	size = this->size();
					size_type	new_size = count < size * 2 ? size * 2 : count;
					pointer		_start(this->allocator.allocate(new_size));
					pointer		_finish(_start);

					_finish = pointer();
					_finish = ft::uninitialized_copy(this->start, this->finish, _start);
					for (size_type i = size;i < count;i++)
						this->allocator.construct(_finish++, value);
					this->destroy_it(this->start, this->finish);
					this->deallocate(this->start, this->end_of_storage - this->start);
					this->start = _start;
					this->finish = _finish;
					this->end_of_storage = _start + new_size;
				}

				void	assign_fill(size_type count, const_reference value)
				{
					size_type capacity = this->capacity();

					if (count == 0) return ;
					if (count > capacity)
					{
						this->destroy_it(this->start, this->finish);
						this->deallocate(this->start, this->capacity());
						this->start = this->allocator.allocate(count);
						capacity = count;
					}
					this->finish = this->start;
					this->end_of_storage = this->start + capacity;
					for (size_type i = 0;i < count;i++)
						this->allocator.construct(this->finish++, value);
				}

				template<class InputIt>
				void	assign_range(InputIt first, InputIt last)
				{
					size_type count = ft::iter_size(first, last);
					size_type capacity = this->capacity();
					
					if (first == last) return ;
					if (count > this->capacity())
					{
						this->destroy_it(this->start, this->finish);
						this->deallocate(this->start, this->capacity());
						this->start = this->allocator.allocate(count);
						capacity = count;
					}
					this->finish = this->start;
					this->end_of_storage = this->start + capacity;
					for (;first != last;++first)
						this->allocator.construct(this->finish++, *first);
				}

				iterator	_erase(iterator pos)
				{
					iterator first = this->begin() + (pos - this->begin());
					
					if (first + 1 != this->end())
						for (iterator it = first + 1;it != this->end();++it, (void)++first)
							*first = *it;
					--this->finish;
					this->allocator.destroy(this->finish);
					return (this->begin() + (pos - this->begin()));
				}
				
				iterator	_erase_range(iterator first, iterator last)
				{
					iterator _first = first;

					if (first != last)
					{
						if (last != end())
							for (iterator it = last;it != end();++it, ++_first)
								*_first = *it;
						this->erase_at_end(&(*_first));
					}
					return (first);	
				}

				template<class InputIt>
				void	destroy_it(InputIt first, InputIt last)
				{
					for (;first != last; ++first)
						this->allocator.destroy(first);
				}

				void	_swap(vector &other)
				{
					ft::swap(&other.start, &this->start);
					ft::swap(&other.finish, &this->finish);
					ft::swap(&other.end_of_storage, &this->end_of_storage);
				}
	};

	template<class T, class Allocator>
	bool	operator==(const ft::vector<T, Allocator>& a, const ft::vector<T, Allocator>& b)
	{
		return (a.size() == b.size() && ft::equal(a.begin(), a.end(), b.begin()));
	}

	template<class T, class Allocator>
	bool	operator!=(const ft::vector<T, Allocator>& a, const ft::vector<T, Allocator>& b)
	{
		return (!(a == b));
	}

	template<class T, class Allocator>
	bool	operator<(const ft::vector<T, Allocator>& a, const ft::vector<T, Allocator>& b)
	{
		return (ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()));
	}

	template<class T, class Allocator>
	bool	operator>(const ft::vector<T, Allocator>& a, const ft::vector<T, Allocator>& b)
	{
		return (b < a);
	}

	template<class T, class Allocator>
	bool	operator<=(const ft::vector<T, Allocator>& a, const ft::vector<T, Allocator>& b)
	{
		return (!(b < a));
	}

	template<class T, class Allocator>
	bool	operator>=(const ft::vector<T, Allocator>& a, const ft::vector<T, Allocator>& b)
	{
		return (!(a < b));
	}

	template< class T, class Alloc >
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif