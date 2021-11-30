/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 03:37:48 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/29 18:07:19 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <memory>
#include "common.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "avltree.hpp"

namespace ft
{

	template<class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key																		key_type;
			typedef T																		mapped_type;
			typedef ft::pair<const Key, T>													value_type;
			typedef size_t																	size_type;
			typedef ptrdiff_t																difference_type;
			typedef Compare																	key_compare;
			typedef ft::AVLTree<value_type, mapped_type, key_type, key_compare>				avl_tree;
			typedef typename avl_tree::node_pointer											node_pointer;
			typedef typename Allocator::template rebind<value_type>::other					allocator_type;
			typedef typename allocator_type::reference										reference;
			typedef typename allocator_type::const_reference								const_reference;
			typedef typename allocator_type::pointer										pointer;
			typedef typename allocator_type::const_pointer									const_pointer;
			typedef typename avl_tree::iterator		 										iterator;
			typedef typename avl_tree::const_iterator	 									const_iterator;
			typedef typename avl_tree::reverse_iterator	 									reverse_iterator;
			typedef typename avl_tree::const_reverse_iterator 								const_reverse_iterator;		
		public:
			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Allocator>;
				protected:
					Compare comp;

					value_compare(Compare _comp) : comp(_comp) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const
					{
						return (comp(x.first, y.first));
					}
			};
		public:
			// MEMBERS FUNCTIONS
			map() : tree(), comp(), allocator() {}
			
			template<class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : tree(), comp(comp), allocator(alloc)
			{
				(void)comp;
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
					
			}

			map(const map& other) : tree(), comp(), allocator()
			{
				if (*this != other)
					*this = other;
			}

			~map() {}

			allocator_type	get_allocator() const
			{
				return (this->allocator);
			}

			map&	operator=(const map& other)
			{
				if (*this != other)
					this->_copy(other.begin(), other.end());
				return (*this);
			}
			
			// ELEMENT ACCESS
			T&			at(const key_type& key)
			{
				node_pointer result = this->tree.find(key);

				if (this->size() == 0 || result == NULL)
					throw std::out_of_range("map::at");
				return (result->value.second);
			}

			const T&	at(const key_type& key) const
			{
				node_pointer result = this->tree.find(key);

				if (this->size() == 0 || result == NULL)
					throw std::out_of_range("map::at");
				return (result->value.second);
			}

			T&			operator[](const key_type& key)
			{
				node_pointer n = this->tree.find(key);

				if (n != NULL)
					return (n->value.second);
				return (this->insert(ft::make_pair(key, T())).first->second);
			}
			
			// CAPACITY
			size_type	size() const
			{
				return (this->tree.size());
			}

			bool		empty() const
			{
				return (this->size() == 0);
			}

			size_type	max_size() const
			{
				return (this->tree.allocator.max_size());
			}
			
			// ITERATORS
			iterator 				begin()
			{
				return iterator(this->tree.left_eot ? this->tree.left_eot->parent : this->tree.default_eot);
			}

			const_iterator			begin() const
			{
				return const_iterator(this->tree.left_eot ? this->tree.left_eot->parent : this->tree.default_eot);
			}
			
			iterator 				end()
			{
				return iterator(this->tree.right_eot ? this->tree.right_eot : this->tree.default_eot);
			}

			const_iterator			end() const
			{
				return const_iterator(this->tree.right_eot ? this->tree.right_eot : this->tree.default_eot);
			}
			
			reverse_iterator		rend()
			{
				return reverse_iterator(this->begin());
			}
			
			const_reverse_iterator 	rend() const
			{
				return const_reverse_iterator(this->begin());
			}

			reverse_iterator 		rbegin() 
			{
				return reverse_iterator(this->end());
			}

			const_reverse_iterator 	rbegin() const
			{
				return const_reverse_iterator(this->end());
			}

			// MODIFIERS
			void						clear()
			{
				this->tree.destroy();
			}
			
			ft::pair<iterator, bool>	insert(const value_type& value)
			{
				std::cout << "WTF\n";
				bool inserted = this->tree.insert(value) == 1 ? true : false;

				return (ft::make_pair<iterator, bool>(iterator(this->tree.find(value.first)), inserted));
			}

			iterator					insert(iterator hint, const value_type& value)
			{
				(void)hint;
				(void)value;
				return (iterator());
			}

			void						erase(iterator pos)
			{
				this->tree.remove((*pos).first);
			}

			void						erase(iterator first, iterator last)
			{
				for(;first != last;++first)
					this->tree.remove((*first).first);
			}

			void						swap(map &other)
			{
				ft::swap(&this->tree, &other.tree);
			}
			
			// LOOKUP
			size_type								count(const key_type& key)
			{
				return (this->tree.find(key) == NULL ? 0 : 1);
			}

			iterator								find(const key_type& key)
			{
				node_pointer n = this->find(key);

				return (n == NULL ? this->end() : iterator(n));
			}
			
			const_iterator							find(const key_type& key) const
			{
				node_pointer n = this->find(key);

				return (n == NULL ? this->end() : const_iterator(n));
			}

			iterator								lower_bound(const Key& key)
			{
				return (iterator(this->tree.lower_bound(*(this->begin(), *(this->end()), key))));
			}

			const_iterator							lower_bound(const Key& key) const
			{
				return (const_iterator(this->tree.lower_bound(*(this->begin(), *(this->end()), key))));
			}

			iterator								upper_bound(const Key& key)
			{
				return (iterator(this->tree.upper_bound(*(this->begin(), *(this->end()), key))));
			}

			const_iterator							upper_bound(const Key& key) const
			{
				return (const_iterator(this->tree.upper_bound(*(this->begin(), *(this->end()), key))));
			}

			ft::pair<iterator,iterator>				equal_range(const Key& key)
			{
				return (ft::make_pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key)));
			}

			ft::pair<const_iterator,const_iterator>	equal_range(const Key& key) const
			{
				return (ft::make_pair<const_iterator, const_iterator>(this->lower_bound(key), this->upper_bound(key)));
			}
			
			// OBSERVERS
			key_compare key_comp()
			{
				return (key_compare());
			}

			map::value_compare value_comp() const
			{
				return (map::value_compare());
			}
		public:
			avl_tree		tree;
		private:
			key_compare		comp;
			allocator_type	allocator;

			template<class InputIt>
			void			_copy(InputIt first, InputIt last)
			{
				this->tree.destroy();
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
			}
	};

	template<class Key, class T, class Compare, class Allocator>
	inline bool	operator==(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{
		return (lhs.tree == rhs.tree);
	}

	template<class Key, class T, class Compare, class Allocator>
	inline bool	operator<(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{
		return (lhs.tree < rhs.tree);
	}

	template<class Key, class T, class Compare, class Allocator>
	inline bool	operator!=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{
		return (!(lhs.tree == rhs.tree));
	}

	template<class Key, class T, class Compare, class Allocator>
	inline bool	operator>(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{
		return (rhs.tree < lhs.tree);
	}

	template<class Key, class T, class Compare, class Allocator>
	inline bool	operator<=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{
		return (!(rhs.tree < lhs.tree));
	}

	template<class Key, class T, class Compare, class Allocator>
	inline bool	operator>=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{
		return (!(lhs.tree < rhs.tree));
	}

	template< class Key, class T, class Compare, class Allocator>
	void swap(ft::map<Key, T, Compare, Allocator>& lhs, ft::map<Key,T,Compare,Allocator>& rhs)
	{
		lhs.swap(rhs);
	}
};

#endif