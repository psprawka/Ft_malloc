/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_rbtrees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:22:35 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/30 16:22:49 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	rotation_left(t_rbtree *root, t_rbtree *root_parent)
{
	root->parent = root->right;
	root->right->left->parent = root;
	root->right = root->right->left;
	root->parent->left = root;
	root = root->parent;
	root->parent = root_parent;
}

void	rotation_right(t_rbtree *root, t_rbtree *root_parent)
{
	root->parent = root->left;
	root->left->right->parent = root;
	root->left = root->left->right;
	root->parent->right = root;
	root = root->parent;
	root->parent = root_parent;
}

void	create_node(t_rbtree *root, short size)
{
	
	
	
}

void	insert_node(t_rbtree *root, short size)
{
	t_rbtree *rptr;
	
	rptr = root;
	while (rptr && )
	{
		if (rptr rptr->left )
		rptr =
		
	}
	
	
	
	
	
}
