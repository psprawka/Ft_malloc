/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 10:45:34 by psprawka          #+#    #+#             */
/*   Updated: 2018/10/07 14:46:02 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


t_pages	*update_display_info(void *head, long pages, bool ifreturn)
{
	static t_pages	info;
	
	if (ifreturn == true)
		return (&info);
	info.pages_nb += pages;
	if (!info.head)
		info.head = head;
	return (NULL);
	
}

void	count_size(size_t size, t_malloc *malloc_info)
{
	size_t	pages;
	
	pages = size / 4096;
	if (size % 4096 != 0)
		pages += 1;
	update_display_info(NULL, (long)pages, 0);
	malloc_info->pages = pages;
	malloc_info->mapped_size = pages * getpagesize();
}

void	show_alloc_mem(void)
{
	t_pages			*info;
	t_segment_tag	*page_tag;
	t_rbnode			*tag;
	void			*ptr;
	long				i;
	long			bytes = 0;
	long	 		total = 0;

	i = 0;
	info = update_display_info(NULL, 0, 1);
	ptr = info->head;
	while (1)
	{
		if (i % getpagesize() == 0 && i == bytes)
		{
			if (i != 0)
				ptr = page_tag->nextpage;
			i = 0;
			if (!ptr)
				break ;
			page_tag = (t_segment_tag *)ptr;
			i += sizeof(t_segment_tag);
			bytes = page_tag->pages * getpagesize();
		}
		tag = (t_rbnode *)(&(ptr[i]));
		if (tag->color_free & USED && (total += tag->size + sizeof(t_rbnode)))
			ft_printf("%p - %p: %ld bytes\n", &(ptr[i]), &(ptr[i]) + tag->size
					  + sizeof(t_rbnode), tag->size + sizeof(t_rbnode));
		else
			ft_printf("%s%p - %p: %ld bytes%s\n", GREEN, &(ptr[i]), &(ptr[i]) + tag->size
					  + sizeof(t_rbnode), tag->size + sizeof(t_rbnode), NORMAL);
		i += sizeof(t_rbnode) + tag->size;
	}
	ft_printf("Total: %ld\n\n", total);
}

void	print_tree(t_rbnode *ptr)
{
	if (!ptr)
		return ;
	printf("%s%zu %s	| left: %zu	| right: %zu	| parent: %zu%s\n", MAROON, ptr->size, ptr->color_free & RED ? "R" : "B", ptr->left == NULL ? 0 : ptr->left->size, ptr->right == NULL ? 0 : ptr->right->size, ptr->parent == NULL ? 0 : ptr->parent->size, NORMAL);
	print_tree(ptr->left);
	print_tree(ptr->right);
}
