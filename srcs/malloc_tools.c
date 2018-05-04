/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 10:45:34 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/02 10:45:38 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*	Find_position:
 **	this func traverses through a tree, finds and returns a parent node for new
 **	son. Variable 'size' is son's size. If tree is empty returns null.
 */

t_tag	*find_position(size_t size)
{
	t_tag	*tptr;
	
	tptr = g_tags_tree;
	while (tptr)
	{
		if (tptr->size > size)
		{
			if (!tptr->left)
				return (tptr);
			tptr = tptr->left;
		}
		else
		{
			if (!tptr->right)
				return (tptr);
			tptr = tptr->right;
		}
	}
	return (tptr);
}