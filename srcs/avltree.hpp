/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avltree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 03:36:56 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/28 10:05:01 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# define NODE_TYPE_RED 		1
# define NODE_TYPE_BLACK 	2
# define NODE_TYPE_NIL		NULL

#include "pair.hpp"
#include "common.hpp"

namespace ft
{

	template<class T>
	struct node
	{
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef struct node*		node_pointer;
		
		node_pointer	left;
		node_pointer 	right;
		node_pointer 	parent;
		value_type		value;
		
		node() : left(NULL), right(NULL), parent(NULL), value(NULL) {}
		node(const value_type &_value_type) : left(NULL), right(NULL), parent(NULL), value(_value_type) {}
		node(const node	&src) : left(src.left), right(src.right), parent(src.parent), value(src.value) {}

		void	init(node_pointer parent, const_reference v)
		{
			this->parent = parent;
			this->value = v;
			this->left = NULL;
			this->right = NULL;
		}

		node&	operator=(const node& src)
		{
			if (*this != src)
			{
				this->right = src.right;
				this->left = src.left;
				this->parent = src.parent;
				this->color = src.color;
				this->value = src.value;
			}
			return (*this);
		}
	};

	
	template<class V, class T, class Key, class Compare>
	class AVLTree
	{
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef V															value_type;
			typedef Compare														key_compare;
			typedef	size_t														size_type;
			typedef struct node<value_type>										node;
			typedef node*														node_pointer;
			typedef typename std::allocator<node>								node_allocator_type;
			typedef value_type&													reference;
			typedef const value_type&											const_reference;
		  public:
			typedef AVLTree_iterator<value_type>       iterator;
			typedef AVLTree_const_iterator<value_type> const_iterator;
			typedef ft::reverse_iterator<iterator>       reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		public:
			AVLTree() : root(NULL), nodes_count(0), compare(), allocator() {}
			
			~AVLTree()
			{
				this->destroy(this->root);
			}
		public:
			node_pointer	find(node_pointer root, key_type key)
			{
				if (this->nodes_count == 0)
					return (NULL);
				if (root && root->value.first == key)
					return (root);
				else if (root->left != NULL && this->compare(key, root->value.first))
					return (this->find(root->left, key));
				else if (root->right != NULL)
					return (this->find(root->right, key));
				else
					return (NULL);
			}
		
			node_pointer	find(const key_type& key)
			{
				std::cout << root->value.first << ", " << root->value.second << ", current_key: " << key << std::endl;
				return (this->find(this->root, key));
			}
			
			node_pointer	find_parent(node_pointer root, const_reference v)
			{
				if (this->nodes_count == 0)
					return (NULL);
				if (root->left != NULL && this->compare(v.first, root->value.first))
					return (this->find_parent(root->left, v));
				else if (root->right != NULL)
					return (this->find_parent(root->right, v));
				else
					return (root);
			}
			
			int		max(int a, int b)
			{
				return (a > b ? a : b);
			}

			int		depth(node_pointer n)
			{
				if (n == NULL)
					return (0);
				return (1 + max(this->depth(n->left), this->depth(n->right)));
			}

			void	rotate_left(node_pointer n)
			{
				if (n == NULL) return ;
				node_pointer right = n->right;

				if (n->parent != NULL)
				{
					if (n->parent->right == n)
						n->parent->right = right;
					else
						n->parent->left = right;
				}
				right->parent = n->parent;
				if (right->left != NULL)
					right->left->parent = n;
				n->right = right->left;
				n->parent = right;
				right->left = n;
				if (n == this->root)
					this->root = right;
			}

			void	rotate_right(node_pointer n)
			{
				if (n == NULL) return ;
				node_pointer left = n->left;

				if (n->parent != NULL)
				{
					if (n->parent->left == n)
						n->parent->left = left;
					else
						n->parent->right = left;
				}
				left->parent = n->parent;
				if (left->right != NULL)
					left->right->parent = n;
				n->left = left->right;
				n->parent = left;
				left->right = n;
				if (n == this->root)
					this->root = left;
			}

			void	rebalance(node_pointer n)
			{
				if (n == NULL) return ;
				
				int	depth = this->depth(n->right) - this->depth(n->left);
				if (depth == 2)
				{
					if (this->depth(n->right->right) - this->depth(n->right->left) == -1)
						this->rotate_right(n->right);
					this->rotate_left(n);
				}
				else if (depth == -2)
				{
					if (this->depth(n->left->right) - this->depth(n->left->left) == 1)
						this->rotate_left(n->left);
					this->rotate_right(n);
				}
				else
				this->rebalance(n->parent);
			}

			node_pointer	maximum(node_pointer n)
			{
				if (n == NULL)
					return (NULL);
				while (n->right != NULL)
					n = n->right;
				return (n);
			}

			node_pointer	minimum(node_pointer n)
			{
				if (n == NULL)
					return (NULL);
				while (n->left != NULL)
					n = n->left;
				return (n);
			}	

			int		insert(const_reference v)
			{
				if (this->find(this->root, v.first))
					return (0);
				node_pointer	potential_parent = this->find_parent(this->root, v);
				node_pointer	new_node = this->allocator.allocate(1);
				new_node->init(potential_parent, v);
				if (new_node == NULL)
					return (0);
				if (potential_parent == NULL)
					this->root = new_node;
				else if (this->compare(new_node->value.first, potential_parent->value.first))
					potential_parent->left = new_node;
				else
					potential_parent->right = new_node;
				this->nodes_count++;
				this->rebalance(new_node);
				return (1);
			}

			int		remove(key_type key)
			{
				node_pointer node;
				
				if (!(node = this->find(this->root, key)))
					return (0);
				if (this->nodes_count > 1)
				{
					node_pointer max = this->maximum(node);

					if (max == NULL)
					{
						if (node == this->root)
							this->root = node->right;
						else if (node->parent->left == node)
							node->parent->left = node->right;
						else
							node->parent->right = node->right;
						if (node->right != NULL)
							node->right->parent = node->parent;
					}
					else
					{
						node->value = max->value;
						if (max->parent->left == max)
							max->parent->left = max->left;
						else
							max->parent->right = max->left;
						if (max->left != NULL)
							max->left->parent = max->parent;
						node = max;
					}
					this->rebalance(node->parent);
				}
				else
					this->root = NULL;
				
				this->nodes_count--;
				this->allocator.destroy(node);
				this->allocator.deallocate(node, 1);
				return (1);
			}

			void		destroy(node_pointer n)
			{
				if (n == NULL) return ;

				if (n->left != NULL)
					destroy(n->left);
				if (n->right != NULL)
					destroy(n->right);
				this->allocator.destroy(n);
				this->allocator.deallocate(n, 1);
			}

			void		destroy(void)
			{
				this->destroy(this->root);
				this->root = NULL;
			}

			size_type	size() const
			{
				return (this->nodes_count);
			}

			node_allocator_type	get_allocator() const
			{
				return (this->allocator);
			}
		protected:
			node_pointer		root;
			size_type			nodes_count;
			key_compare			compare;
			node_allocator_type	allocator;
	};

	template<typename T>
	node<T>*	increment_tree_node(node<T>* n)
	{
		if (n->right != NULL)
		{
			n = n->right;
			while (n->left != NULL)
				n = n->left;
		}
		else
		{
			node<T>* tmp = n->parent;
			while (n == tmp->right)
			{
				n = tmp;
				tmp = tmp->parent;
			}
			if (n->right != tmp)
				n = tmp;
		}
		return (n);
	}

	template<typename T>
	node<T>*	decrement_tree_node(node<T>* n)
	{
		if (n->left != NULL)
		{
			n = n->left;
			while (n->right != NULL)
				n = n->right;
		}
		else
		{
			node<T> tmp = n->parent;
			while (n == tmp->left)
			{
				n = tmp;
				tmp = tmp->parent;
			}
			n = tmp;
		}
		return (n);
	}

	template<typename T>
	struct	AVLTree_iterator
	{
		typedef T							value_type;
		typedef value_type&					reference;
		typedef T*							pointer;
		typedef bidirectional_iterator_tag	iterator_category;
      	typedef ptrdiff_t                 	difference_type;
		typedef struct node<T>*				node_pointer;
		typedef AVLTree_iterator<T>			self;
	
		AVLTree_iterator() : current() {}

		AVLTree_iterator(node_pointer src) : current(src) {}

		reference			operator*() const
		{
			return (this->current->value);
		}

		pointer				operator->() const
		{
			return (&(this->current->value));
		}

		self&	operator++()
		{
			this->current = ft::increment_tree_node(this->current);
			return (*this);
		}

		self	operator++(int)
		{
			self	tmp = *this;
			this.current = ft::increment_tree_node(this->current);
			return (tmp)
		}

		self&	operator--()
		{
			this->current = ft::decrement_tree_node(this->current);
			return (*this);
		}

		self	operator--(int)
		{
			self tmp = *this;
			this->current = ft::decrement_tree_node(this->current);
			return (tmp);
		}

		bool	operator==(const self& x) const
     	{
			return (this->current == x.current);
		}

		bool	operator!=(const self& x) const
     	{
			return !(this->current == x.current);
		}
		
		public:
			node_pointer current;
	};

	template<typename T>
	struct	AVLTree_const_iterator
	{
		typedef T							value_type;
		typedef const value_type&			reference;
		typedef const T*					pointer;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef AVLTree_iterator<T>			iterator;
      	typedef ptrdiff_t                 	difference_type;
		typedef struct node<T>*				node_pointer;
		typedef AVLTree_iterator<T>			self;
	
		AVLTree_const_iterator() : current() {}

		AVLTree_const_iterator(node_pointer src) : current(src) {}

		AVLTree_const_iterator(const iterator& src) : current(src.current) {}

		reference			operator*() const
		{
			return (this->current->value);
		}

		pointer				operator->() const
		{
			return (&(this->current->value));
		}

		self&	operator++()
		{
			this->current = ft::increment_tree_node(this->current);
			return (*this);
		}

		self	operator++(int)
		{
			self	tmp = *this;
			this.current = ft::increment_tree_node(this->current);
			return (tmp)
		}

		self&	operator--()
		{
			this->current = ft::decrement_tree_node(this->current);
			return (*this);
		}

		self	operator--(int)
		{
			self tmp = *this;
			this->current = ft::decrement_tree_node(this->current);
			return (tmp);
		}

		bool	operator==(const self& x) const
     	{
			return (this->current == x.current);
		}

		bool	operator!=(const self& x) const
     	{
			return !(this->current == x.current);
		}
		
		public:
			node_pointer current;
	};

}

#endif