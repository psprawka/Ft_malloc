/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:21:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/30 16:21:18 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <string.h>

t_tag	*g_tags_tree = NULL;


/*
**	find_free_node:
**	this tool takes a desired size and finds the most appropiate node that would
**	fit new malloc. Function goes till the end of a tree, but may break before
**	hitting the end. When size is the same, it returns a current node, if malloc
**	size is bigger than node size, we're moving on the right outer branch of
**	the tree until we find a proper node. If node big enoungh doesn't exist,
**	return null. When size is less than node size, function checks next left
**	node and copares size. If size is still less than node size, it moves to
**	left child, otherwise current node is returned.
*/

void	*find_free_node(size_t size)
{
	t_tag	*tptr;
	
	tptr = g_tags_tree;
	while (tptr)
	{

		if (tptr->size == size && tptr->color_free & FREE)
			return ((void *)tptr);
		else if (tptr->size > size)
		{
			if ((tptr->left && tptr->left->size > size) || tptr->color_free & USED)
				tptr = tptr->left;
			else
				return ((void *)tptr);
		}
		else
		{
			if (tptr->right)
				tptr = tptr->right;
			else
				return (NULL);
		}
	}
	return ((void *)tptr);
}

/*
**	Map_memory:
**	this function maps memory; first, it traverses through the tree and tries to
**	find a free space where our new size malloc would fit. If it's positive,
**	reuse_tag will be called, will change tag->size on freespace addres to size
**	and set mapped to total previous avaliable free space. If node wasn't found,
**	function uses mmap to create a new map based on the size, then section's tag
**	is inserted with size 'size' and flag USED on freespace. Then I insert new
**	free tag on size + header with full avaliable size without desired 'size
**	with flag FREE. Function returns a pointer pointing at section's tag.
*/


void	add_next_page(void *newpage)
{
	t_info			*info;
	void			*pptr;
	t_segment_tag	*page_tag;

	info = update_display_info(NULL, 0, 1);
	if (!info->head)
	{
		update_display_info(newpage, 0, 0);
		return ;
	}
	page_tag = (t_segment_tag *)info->head;
	while (page_tag->nextpage)
	{
		pptr = page_tag->nextpage;
		page_tag = (t_segment_tag *)pptr;
	}
	page_tag->nextpage = newpage;
}



void	*map_memory(size_t size)
{
	void			*mptr;
	t_tag			*free_tag;
	size_t			mapped;
	long			pages = 0;
	t_segment_tag	 *page_tag;

	if ((mptr = find_free_node(size)) != NULL)
		reuse_tag(mptr, size, &mapped);
	else
	{
		if (IS_TINY(size))
		{
			mapped = count_size(100 * TINY, &pages);
			mptr = mmap(NULL, mapped, PROT_READ | PROT_WRITE | PROT_EXEC,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		}
		else if (IS_SMALL(size))
		{
			mapped = count_size(100 * SMALL, &pages);
			mptr = mmap(NULL, mapped, PROT_READ | PROT_WRITE | PROT_EXEC,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		}
		else
		{
			mapped = count_size(size + sizeof(t_segment_tag), &pages);
			mptr = mmap(NULL, mapped, PROT_READ | PROT_WRITE | PROT_EXEC,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		}
		add_next_page(mptr);
		page_tag = (t_segment_tag *)mptr;
		page_tag->pages = pages;
 		mptr += sizeof(t_segment_tag);
		mapped -= sizeof(t_segment_tag);
		if (mapped > (size + sizeof(t_tag) + sizeof(t_tag)))
			insert_tag(mptr, mptr - sizeof(t_segment_tag), size, false);
		else
			insert_tag(mptr, mptr - sizeof(t_segment_tag), size + (mapped - size - sizeof(t_tag)), false);
		mapped -= sizeof(t_tag);
	}
	free_tag = (t_tag *)mptr;
	if (mapped > (free_tag->size + sizeof(t_tag)))
	{
		insert_tag(mptr + sizeof(t_tag) + free_tag->size, free_tag->head,
		mapped - free_tag->size - sizeof(t_tag), true);
	}
	return (mptr);
}

void	*ft_malloc(size_t size)
{
	void *mptr;

	if (size == 0)
		return (NULL);
	mptr = map_memory(size);
	mptr += sizeof(t_tag);
	show_alloc_mem();
	return (mptr);
}

int		main(void)
{
	char *ptr;
	char *ptr1;
	char *ptr2 = NULL;

	ptr = ft_malloc(9);
	ptr2 = ft_malloc(960);
	ptr1 = ft_malloc(11700);
	ptr = ft_malloc(1);
	ptr = ft_malloc(40);
	ptr = ft_malloc(0);
	ptr = ft_malloc(2147483648);
	ptr = ft_malloc(10);
	ptr = ft_malloc(4000);
	ptr = ft_malloc(2200);
	ptr = ft_malloc(3333);
	ptr2 = ft_malloc(3567);
	ptr = ft_malloc(4753);
	ptr = ft_malloc(22344);
	
	ptr = ft_malloc(3693);
	ptr2 = ft_malloc(3014);
	ptr2 = ft_malloc(2000);
	ptr = ft_malloc(500);
	ptr = ft_malloc(2002);
//	ptr = ft_malloc(330);
	ptr = ft_malloc(130);
	ptr = ft_malloc(1112);
	
	ptr2 = ft_malloc(339);
	ptr = ft_malloc(456);
//	ptr = ft_malloc(151);
	ptr = ft_malloc(120);
	ptr = ft_malloc(313);
	ptr = ft_malloc(3693);
	ptr2 = ft_malloc(3014);
	
//	ptr = ft_malloc(9);
//	ptr2 = ft_malloc(960);
//	ptr1 = ft_malloc(11700);
//	ptr = ft_malloc(1);
//	ptr = ft_malloc(40);
//	ptr = ft_malloc(0);
//	ptr = ft_malloc(2147483648);
//	ptr = ft_malloc(10);
//	ptr = ft_malloc(4000);
//	ptr = ft_malloc(2200);
//	ptr = ft_malloc(3333);
//	ptr = ft_malloc(123423342);
//	ptr = ft_malloc(40);
//	ptr = ft_malloc(2);
//	ptr = ft_malloc(637);
//	ptr = ft_malloc(1);
//	ptr = ft_malloc(42);
//	ptr = ft_malloc(5);
//	ptr = ft_malloc(466);
//	ptr2 = ft_malloc(3567);
//	ptr = ft_malloc(4753);
//	ptr = ft_malloc(22234344);
//	ptr = ft_malloc(3693);
//	ptr2 = ft_malloc(3204);
//	ptr2 = ft_malloc(2000);
//	ptr = ft_malloc(5);
//	ptr = ft_malloc(2000);
//	ptr = ft_malloc(334230);
//	ptr = ft_malloc(130);
//	ptr = ft_malloc(12);
//	ptr2 = ft_malloc(339);
//	ptr = ft_malloc(456);
//	ptr = ft_malloc(1);
//	ptr = ft_malloc(120);
//	ptr = ft_malloc(313);
//	ptr = ft_malloc(33);
//	ptr2 = ft_malloc(3014);
	ptr = strcpy(ptr, "hello");
	ptr2 = strcpy(ptr2, "adam sucks");
	ft_printf("[%s][%s]\n", ptr, ptr2);
	return (0);
}
