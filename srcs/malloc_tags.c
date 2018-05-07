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
	
	printf("%sINSERTION%s\n", CYAN, NORMAL);
	new = (t_tag *)mptr;
	if (if_free == true)
		printf("%sINSERTING A FREE NODE: %p %zu\n%s", CYAN, new, size, NORMAL);
	if (if_free == false)
	{
		seg_tag = (t_segment_tag *)head;
		seg_tag->to_free += 1;
	}
	seg_tag = (t_segment_tag *)head;
//	printf("TO_FREE %d\n", seg_tag->to_free);
//	ft_printf("here0 %p\n", new);
	new->parent = NULL;
//	ft_printf("here1\n");
	new->left = NULL;
//	ft_printf("here2\n");
	new->right = NULL;
//	ft_printf("here3\n");
	new->head = head;
//	ft_printf("here4\n");
	new->color_free = RED;
//	ft_printf("here5\n");
	new->color_free |= (if_free == true ? FREE : USED);
//	ft_printf("here6\n");
	new->size = size;
//	ft_printf("inserting to a tree\n");
	if (if_free == true)
	{
		ft_printf("inserting to a tree\n");
		insertion(new);
		ft_printf("insertion finished\n");
		print_tree(g_tags_tree);
//		print_tree(g_tags_tree);
	}
//	ft_printf("insertion finished\n");
	find_position(13000);
	find_position(1);
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
	printf("%sREUSING A NODE: %p %zu\n%s", CYAN, mptr, reuse->size, NORMAL);
//	reuse->color_free = RED;
//	reuse->color_free |= USED;
	*remainder = reuse->size;
	if (reuse->size < size + sizeof(t_tag) + 1)
		size += reuse->size - size;
	//	reuse->size = size;
	seg_tag->to_free -= 1;
	printf("deleting.. %zu, new size: %zu\n", reuse->size, size);
	print_tree(g_tags_tree);
	deletion(reuse);
	ft_printf("after deletion\n");
	print_tree(g_tags_tree);
	insert_tag(mptr, reuse->head, size, false);
}
