/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_deletion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:38:35 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/04 10:38:37 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	delete_two_children(t_tag *to_delete)
{
	t_tag *to_replace;

	if (!to_delete->right->left)
	{
		if (to_delete->parent && to_delete->parent->right == to_delete)
			to_delete->parent->right = to_delete->right;
		else if (to_delete->parent && to_delete->parent->left == to_delete)
			to_delete->parent->left = to_delete->right;
		to_delete->right->parent = to_delete->parent;
		to_delete->right->left = to_delete->left;
		to_delete->left->parent = to_delete->right;
	}
	else
	{
		to_replace = to_delete->right->left;
		while (to_replace->left)
			to_replace = to_replace->left;
		to_replace->parent->left = to_replace->right;
		if (to_replace->right)
			to_replace->right->parent = to_replace->parent;
		to_replace->left = to_delete->left;
		to_delete->left->parent = to_replace;
		to_replace->right = to_delete->right;
		to_delete->right->parent = to_replace;
		to_replace->parent = to_delete->parent;
	}
}

void	deletion(t_tag *to_delete)
{
	if (!to_delete->parent)
		g_tags_tree = NULL;
	else if (!to_delete->left && !to_delete->right)
	{
		if (to_delete->parent->right == to_delete)
			to_delete->parent->right = NULL;
		else
			to_delete->parent->left = NULL;
	}
	else if (!to_delete->left && to_delete->right)
	{
		if (to_delete->parent->right == to_delete)
			to_delete->parent->right = to_delete->right;
		else
			to_delete->parent->left = to_delete->right;
		to_delete->right->parent = to_delete->parent;
	}
	else if (to_delete->left && !to_delete->right)
	{
		if (to_delete->parent->right == to_delete)
			to_delete->parent->right = to_delete->left;
		else
			to_delete->parent->left = to_delete->left;
		to_delete->left->parent = to_delete->parent;
	}
	else if (to_delete->left && to_delete->right)
		delete_two_children(to_delete);
}
