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
	ft_printf("%d\n", size);
	while (tptr)
	{
//		ft_printf("tptr: %d | left: %p right: %p\n", tptr->size, tptr->left, tptr->right);
		if (tptr->size == size && tptr->color_free & FREE)
		{
			ft_printf(" %d\n",  tptr->size);
//			ft_printf("%sFOUND FREE NODE %p %d%s\n", MAGNETA, tptr, size, NORMAL);
			return ((void *)tptr);
		}
		else if (tptr->size > size)
		{
			if ((tptr->left && tptr->left->size > size) || tptr->color_free & USED)
			{
				ft_printf("moving to left ");
				ft_printf(" %d -> ",  tptr->size);
//
				tptr = tptr->left;
			}
			else
			{
				ft_printf("left %d\n", tptr->size);
//				ft_printf("%sFOUND FREE NODE %p %d%s\n", ORANGE, tptr, size, NORMAL);
				return ((void *)tptr);
			}
		}
		else
		{
			if (tptr->right)
			{
				ft_printf("moving to right %d -> ", tptr->size);
				tptr = tptr->right;
			}
			else
			{
				ft_printf("not big enough\n");
				return (NULL);
			}
		}
	}
	ft_printf("return void\n");
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

void	*map_memory(size_t size)
{
	void	*mptr;
	t_tag	*free_tag;
	int		mapped;

	if ((mptr = find_free_node(size)) != NULL)
		reuse_tag(mptr, size, &mapped);
	else
	{
//		ft_printf("new page %d\n", size);
		if (IS_TINY(size))
		{
//			ft_printf("TINY %d\n", TINY);
			mapped = 100 * TINY;
			mptr = mmap(NULL, mapped, PROT_READ | PROT_WRITE | PROT_EXEC,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		}
		else if (IS_SMALL(size))
		{
//			ft_printf("SMALL\n");
			mapped = 100 * SMALL;
			mptr = mmap(NULL, mapped, PROT_READ | PROT_WRITE | PROT_EXEC,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		}
		else
		{
//			ft_printf("LARGE\n");
			mapped = size + sizeof(t_page_tag);
			mptr = mmap(NULL, size , PROT_READ | PROT_WRITE | PROT_EXEC,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		}
//		ft_printf("%sThe beginning of a page %p %d\n%s", CYAN, mptr, size, NORMAL);
 		mptr += sizeof(t_page_tag);
//		ft_printf("%sAfter page tag: %p %d\n%s", CYAN, mptr, size, NORMAL);
		mapped -= sizeof(t_page_tag);
		insert_tag(mptr, mptr - sizeof(t_page_tag), size, false);
	}
//	ft_printf("%sFound: %p %d\n%s", CYAN, mptr, size, NORMAL);
	free_tag = (t_tag *)mptr;
	if ((int)(mapped - free_tag->size - sizeof(t_tag)) > 0)
	{
//		ft_printf("here [%d]\n", mapped - free_tag->size - sizeof(t_tag));
		insert_tag(mptr + sizeof(t_tag) + free_tag->size, free_tag->head,
		mapped - free_tag->size - sizeof(t_tag), true);
	}
//	ft_printf("%sFound: %p %d\n%s", CYAN, mptr, size, NORMAL);
	return (mptr);
}

void	*ft_malloc(size_t size)
{
	void *mptr;
//	ft_printf("%d %s!! NEW MALLOC %d!!\n%s", sizeof(t_tag), GREEN, size, NORMAL);
	if (size == 0 || size > 2147483647)
		return (NULL);
	mptr = map_memory(size);
	mptr += sizeof(t_tag);
//	ft_printf("%sRETURNING THIS PTR: %p %d\n%s", YELLOW, mptr, size, NORMAL);
	return (mptr);
}

int		main(void)
{
	char *ptr;
	char *ptr1;
	char *ptr2;

	ptr = ft_malloc(9);
	ptr2 = ft_malloc(960);
	ptr1 = ft_malloc(11700);
	ptr = ft_malloc(1);
	ptr = ft_malloc(40);
	ptr = ft_malloc(0);
	ptr = ft_malloc(2147483648);
	ptr = ft_malloc(10);
	ptr = strcpy(ptr, "hello");
	ptr2 = strcpy(ptr2, "adam sucks");
	ft_printf("[%s][%s]\n", ptr, ptr2);
	return (0);
}
