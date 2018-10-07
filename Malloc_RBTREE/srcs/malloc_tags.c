/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:22:35 by psprawka          #+#    #+#             */
/*   Updated: 2018/09/02 01:06:50 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*	Create_tag:
**	Create tag creates a section tag and assigns it to mapped_size memory. During
**	initialization, following variables are being assigned: head, color, size
**	and if section is used/freed. The other atributes are set further, when
**	free/used node are added to a tree.
*/

void	insert_tag(t_malloc *malloc_info, void *head, bool if_free)
{
	t_rbnode			*new;
	t_segment_tag 	*seg_tag;

	if (if_free == true)
		printf("%sINSERTING A FREE NODE: size: %zu%s\n", CYAN, malloc_info->size, NORMAL);
	if (!if_free)
	{
		seg_tag = (t_segment_tag *)head;
		seg_tag->to_free += 1;
	}
	new = (t_rbnode *)malloc_info->mptr;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->head = head;
	new->color_free = RED;
	new->color_free |= (if_free == true ? FREE : USED);
	new->size = malloc_info->size;
	printf("Before inserting\n");
	if (if_free)
	{
		printf("Inserting");
		insertion(new);
	}
	printf("After inserting\n");
}

/*	Reuse_tag:
**	This function reuses a tag; it changes following atributes: color, size and
**	if section is used/freed. Size represents total number to allocate, thereby
**	size || size + remainder of free region if there wasn't engouh free memory
**	to fit next tag. Var remainder says how much free space was initially.
*/

void	reuse_tag(t_malloc *malloc_info)
{
	t_rbnode		*reuse;
	
	reuse = (t_rbnode *)malloc_info->mptr;
	malloc_info->mapped_size = reuse->size;
	if (reuse->size < malloc_info->size + sizeof(t_rbnode) + 1) //check if next tag fits
		malloc_info->size = reuse->size;
	deletion(reuse);
	insert_tag(malloc_info, reuse->head, false);
}

// void	reuse_tag(t_malloc *malloc_info)
// {
// 	t_rbnode			*reuse;
// 	t_segment_tag 	*seg_tag;
	
// 	reuse = (t_rbnode *)malloc_info->mptr;
// 	seg_tag = (t_segment_tag *)reuse->head;
// 	*remainder = reuse->size;
// 	if (reuse->size < size + sizeof(t_rbnode) + 1)
// 		size += reuse->size - size;
// 	deletion(reuse);
// 	insert_tag(mptr, reuse->head, size, false);
// }

// insert_tag(malloc_info->mptr + sizeof(t_rbnode) + free_tag->size, free_tag->head, , true);