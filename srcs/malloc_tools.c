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
//		ft_printf("%sfor: %d | tptr: %d | left: %p right: %p%s\n", YELLOW, size, tptr->size, tptr->left, tptr->right, NORMAL);
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

t_info	*update_display_info(void *head, long pages, bool ifreturn)
{
	static t_info	info;
	
	if (ifreturn == true)
		return (&info);
//	printf("%sCOMIN WITH %ld %p\nBEFORE: %p || %ld%s\n", BLUE, pages, head, info.head, info.pages_nb, NORMAL);
	info.pages_nb += pages;
	if (info.head == NULL)
		info.head = head;
//	printf("%sAFTER: %p || %ld%s\n", BLUE, info.head, info.pages_nb, NORMAL);
	return (NULL);
	
}

size_t		count_size(size_t size)
{
	size_t	pages;
	
	pages = size / 4096;
	if (size % 4096 != 0)
		pages += 1;
//	printf("%sPAGES CREATED: [%ld]%s\n", PURPLE, (long)pages, NORMAL);
	update_display_info(NULL, (long)pages, 0);
	pages *= getpagesize();
//	printf("%sTOTAL: [%ld]%s\n", PURPLE, (long)pages, NORMAL);
	return (pages);
}

void	show_alloc_mem(void)
{
	t_info			*info;
	t_segment_tag	*page_tag;
	void			*ptr;
	int				i;
	int				pages_left;

	i = 0;
	info = update_display_info(NULL, 0, 1);
	ptr = info->head;
//	printf("LOOOOOOOOL HERE %ld\n", info->pages_nb);
	while (&(ptr[i]) != (info->head + (info->pages_nb * getpagesize())))
	{
		if (i % getpagesize() == 0 && pages_left == 0)
		{
			page_tag = (t_segment_tag *)(&(ptr[i]));
			i += sizeof(t_segment_tag);
			pages_left = page_tag->pages;
		}
//		printf("")
		pages_left--;
			
		
	}

}

void	print_tree(t_tag *ptr)
{
	if (!ptr)
		return ;
	printf("%s%zu %s	| left: %zu	| right: %zu	| parent: %zu%s\n", MAROON, ptr->size, ptr->color_free & RED ? "R" : "B", ptr->left == NULL ? 0 : ptr->left->size, ptr->right == NULL ? 0 : ptr->right->size, ptr->parent == NULL ? 0 : ptr->parent->size, NORMAL);
	print_tree(ptr->left);
	print_tree(ptr->right);
}
