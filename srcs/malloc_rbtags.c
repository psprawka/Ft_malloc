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

t_tag	*create_tag(t_tag *root, size_t size)
{
	t_tag *new;
	
	new->parent = root;
	new->color = RED;
	new->left = NULL;
	new->right = NULL;
	new->size = size;
	return (new);
}

t_tag	*insert_tag(t_tag *root, size_t size)
{
	t_tag *res;
	
	if (!root)
		return (NULL);
	res = NULL;
	if (root->size >= size && insert_tag(root->right, size) == NULL)
		res = create_tag(root->right, size);
	else if (root->size < size && insert_tag(root->left, size) == NULL)
		res = create_tag(root->left, size);
	return (res);
}

void	valid_tree(t_tag *root)
{
	if (!PARENT)
		root->color = BLACK;
	else if (GRANDPA && (PARENT->color & RED))
	{
		if (UNCLE_RIGHT)
			UNCLE_RIGHT->color = BLACK;
		if (UNCLE_LEFT)
			UNCLE_LEFT->color = BLACK;
		GRANDPA->color = RED;
		valid_tree(GRANDPA);
	}
	else if (GRANDPA && (PARENT->color & BLACK))
	{
		if (GRANDPA->right->left == root)
		{
			rotate_right(PARENT, GRANDPA);
			root = root->right;
		}
		else if (GRANDPA->left->right == root)
		{
			rotate_left(PARENT, GRANDPA);
			root = root->left;
		}
		root == PARENT->left ? rotate_right(GRANDPA) : rotate_left(GRANDPA);
		PARENT->color = BLACK;
		GRANDPA->color = RED;
	}
}

void	insertion(t_tag *root, size_t size)
{
	t_tag *son;
	
	if (root == NULL)
		root = create_tag(root->right, size);
	else
	{
		son = insert_tag(root, size);
		valid_tree(son);
	}
}
