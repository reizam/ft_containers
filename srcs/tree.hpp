/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 03:36:56 by kmazier           #+#    #+#             */
/*   Updated: 2021/11/27 05:48:07 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# define NODE_TYPE_RED 		0
# define NODE_TYPE_BLACK 	1
# define NODE_TYPE_NIL		NULL

#include "pair.hpp"

namespace ft
{
	template<class Key, class T, class Compare, class Allocator>
	class RBTree
	{
		public:
			typedef Key						key_type;
			typedef T						mapped_type;
			typedef ft::pair<const Key, T>	value_type;
			typedef size_t					size_type;
			typedef ptrdiff_t				difference_type;
			typedef Compare					key_compare;
			typedef node*					node_pointer;
		protected:
			template<class T>
			struct tree_node
			{
				node		*left;
				node		*right;
				node		*parent;
				int 		color;
				value_type	value;
			};

			node_pointer	parent(node_pointer	n)
			{
				return (n->parent);
			}

			node_pointer	grand_parent(node_pointer n)
			{
				node_pointer parent = this->parent(n);
				
				if (parent == NULL)
					return (NULL);
				return (this->parent(parent));
			}

			node_pointer	brother(node_pointer n)
			{
				node_pointer parent = this->parent(n);

				if (parent == NULL)
					return (NULL);
				return (parent->right == n ? parent->left : parent->right);
			}

			node_pointer	uncle(node_pointer n)
			{
				node_pointer parent = this->parent(n);
				node_pointer grand_parent = this->grand_parent(n);

				if (grand_parent == NULL)
					return (NULL);
				return (this->brother(parent
				));
			}

			void			rotate_left(node_pointer x)
			{
				node_pointer y = x->right;
				
				x->right = y->left;
				if (y->left != NODE_TYPE_NIL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					x = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void			rotate_right(node_pointer x)
			{
				node_pointer y = x->left;
				
				x->left = y->right;
				if (y->right != NODE_TYPE_NIL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					x = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			node_pointer	find(node_pointer root, key_type key)
			{
				if (root == NULL)
					return (NULL);
				if (root->value.first == key)
					return (root);
				else if (this->key_compare(key, root->value.first))
					return (this->find(root->right, key));
				else
					return (this->find(root->left, key));
			}

			node_pointer	remove(node_pointer root, key_type key)
			{
				if (root == NULL)
					return ;
				
			}

			node_pointer	insert(node_pointer n)
			{
				this->recursive_insert(this->root, n);
				this->insert_repair_tree(n);
				this->root = n;
				while (this->parent(n) != NULL)
					this->root = this->parent(n);
				return (this->root);
			}

			void			recursive_insert(node_pointer root, node_pointer n)
			{
				if (root != NULL)
				{
					if (this->key_compare(n->value.first, root->value.first))
					{
						if (root->left != NODE_TYPE_NIL)
						{
							recursive_insert(root->left, n);
							return ;
						}
						else
							root->left = n;
					}
					else
					{
						if (root->right != NODE_TYPE_NIL)
						{
							recursive_insert(root->right, n);
							return ;
						}
						else
							root->right = n;
					}
				}
				n->parent = root;
				n->left = NODE_TYPE_NIL;
				n->right = NODE_TYPE_NIL;
				n->color = NODE_TYPE_RED;
			}

			void			insert_repair_tree(node_pointer n)
			{
				node_pointer parent = this->parent(n);
				node_pointer grand_parent = this->grand_parent(n);
				node_pointer uncle = this->uncle(n);

				if (parent == NULL)
					n->color = NODE_TYPE_BLACK;
				else if (parent->color == NODE_TYPE_BLACK)
					return ;
				else if (uncle->color == NODE_TYPE_RED)
				{
					parent->color = NODE_TYPE_BLACK;
					uncle->color = NODE_TYPE_BLACK;
					grand_parent->color = NODE_TYPE_RED;
					this->insert_repair_tree(grand_parent);
				}
				else
				{
					if (n == grand_parent->right)
					{
						this->rotate_left(p);
						n = n->left;
					}	
					else if (n == grand_parent->left)
					{
						this->rotate_right(p);
						n = n->right;
					}
					parent = parent(n);
					grand_parent = grand_parent(n);
					if (n == parent->right)
						rotate_right(grand_parent);
					else
						rotate_left(grand_parent);
					
					parent->color = NODE_TYPE_BLACK;
					grand_parent->color = NODE_TYPE_RED;
				}
			}
		public:	
			tree() : root(), key_compare() {}
		private:
			node_pointer	root;
			key_compare		compare;
	};
}

#endif