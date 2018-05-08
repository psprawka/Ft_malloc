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
	t_tag			*new;
	t_segment_tag 	*seg_tag;

	new = (t_tag *)mptr;
	if (if_free == true)
		printf("%sINSERTING A FREE NODE: %p %zu%s\n", CYAN, new, size, NORMAL);
	else
		printf("%sREUSIG NODE: %p %zu%s\n", CYAN, new, size, NORMAL);
	if (if_free == false)
	{
		seg_tag = (t_segment_tag *)head;
		seg_tag->to_free += 1;
	}
	seg_tag = (t_segment_tag *)head;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->head = head;
	new->color_free = RED;
	new->color_free |= (if_free == true ? FREE : USED);
	new->size = size;
	if (if_free == true)
		insertion(new);
}

/*	Reuse_tag:
**	This function reuses a tag; it changes following atributes: color, size and
**	if section is used/freed. Size represents total number to allocate, thereby
**	size || size + remainder of free region if there wasn't engouh free memory
**	to fit next tag. Var remainder says how much free space was initially.
*/

void	reuse_tag(void *mptr, size_t size, size_t *remainder)
{
	t_tag			*reuse;
	t_segment_tag 	*seg_tag;
	
	reuse = (t_tag *)mptr;
	seg_tag = (t_segment_tag *)reuse->head;
	*remainder = reuse->size;
	if (reuse->size < size + sizeof(t_tag) + 1)
		size += reuse->size - size;
	deletion(reuse);
	insert_tag(mptr, reuse->head, size, false);
}
