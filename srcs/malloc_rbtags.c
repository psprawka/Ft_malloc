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

/*	Create_tag:
**	Create tag creates a section tag and assigns it to mapped memory. During
**	initialization, following variables are being assigned: head, color, size
**	and if section is used/freed. The other atributes are set further, when
**	free/used node are added to a tree.
*/

void	insert_tag(void *mptr, void *head, size_t size, bool if_free)
{
	t_tag *new;

	new = (t_tag *)mptr;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->head = head;
	new->color_free = RED;
	new->color_free |= if_free == true ? FREE : USED;
	new->size = size;
}

/*	Reuse_tag:
**	This function reuses a tag; it changes following atributes: color, size and
**	if section is used/freed. Size represents total number to allocate, thereby
**	size || size + remainder of free region if there wasn't engouh free memory
**	to fit next tag. Var remainder says how much free space was initially.
*/

void	reuse_tag(void *mptr, int size, int *remainder)
{
	t_tag	*reuse;
	int		free;
	
	reuse = (t_tag *)mptr;
	reuse->parent = NULL;
	reuse->left = NULL;
	reuse->right = NULL;
	reuse->color_free = RED;
	reuse->color_free |= USED;
	*remainder = reuse->size;
	if (reuse->size < size + sizeof(t_tag) + 1)
		size += reuse->size - size;
	reuse->size = size;
}

void	valid_insertion(t_tag root)
{
	if (!PARENT)
		root.color = BLACK;
	else if (GRANDPA && (PARENT->color & RED))
	{
		if (UNCLE_RIGHT)
			UNCLE_RIGHT.color = BLACK;
		if (UNCLE_LEFT)
			UNCLE_LEFT.color = BLACK;
		GRANDPA.color = RED;
		valid_tree(GRANDPA);
	}
	else if (GRANDPA && (PARENT.color & BLACK))
	{
		if (GRANDPA.right.left == root)
		{
			rotate_right(PARENT, GRANDPA);
			root = root.right;
		}
		else if (GRANDPA.left.right == root)
		{
			rotate_left(PARENT, GRANDPA);
			root = root.left;
		}
		root == PARENT.left ? rotate_right(GRANDPA) : rotate_left(GRANDPA);
		PARENT.color = BLACK;
		GRANDPA.color = RED;
	}
}

//void	insertion(t_tag root, size_t size)
//{
//	t_tag son;
//
//	if (root == NULL)
//		root = create_tag(root.right, size);
//	else
//	{
//		son = insert_tag(root, size);
//		valid_insertion(son);
//	}
//}

