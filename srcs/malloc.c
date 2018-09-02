/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:21:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/09/02 00:57:05 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <string.h>

t_rbnode	*g_tags_tree = NULL;


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

// int		find_free_node(t_malloc *malloc_info)
// {
// 	t_rbnode	*tptr;
	
// 	tptr = g_tags_tree;
// 	while (tptr)
// 	{
// 		if (tptr->size == malloc_info->size && tptr->color_free & FREE)
// 		{
// 			malloc_info->mptr = (void *)tptr;
// 			return (EXIT_SUCCESS);
// 		}
// 		else if (tptr->size > malloc_info->size)
// 		{
// 			if ((tptr->left && tptr->left->size > malloc_info->size) || tptr->color_free & USED)
// 				tptr = tptr->left;
// 			else
// 			{
// 				malloc_info->mptr = (void *)tptr;
// 				return (EXIT_SUCCESS);
// 			}
// 		}
// 		else
// 		{
// 			if (!tptr->right)
// 				return (EXIT_FAILURE);
// 			tptr = tptr->right;		
// 		}
// 	}
// 	return ((void *)tptr);
// }

void	*find_free_node(t_malloc *malloc_info)
{
	t_rbnode	*tptr;
	
	tptr = g_tags_tree;
	while (tptr)
	{
		if (tptr->size == malloc_info->size && tptr->color_free & FREE)
			return ((void *)tptr);
		else if (tptr->size > malloc_info->size)
		{
			if ((tptr->left && tptr->left->size > malloc_info->size) || tptr->color_free & USED)
				tptr = tptr->left;
			else
				return ((void *)tptr);
		}
		else
		{
			if (!tptr->right)
				return (NULL);
			tptr = tptr->right;
		}
	}
	return (NULL);
}
//----------------------------------------------------------------------------------------

void	map_memory(t_malloc *malloc_info)
{
	if (IS_TINY(malloc_info->size))
		count_size(100 * TINY, malloc_info);
	else if (IS_SMALL(malloc_info->size))
		count_size(100 * SMALL, malloc_info);
	else
		count_size(malloc_info->size + sizeof(t_segment_tag), malloc_info);

	malloc_info->mptr = mmap(NULL, malloc_info->mapped_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
}

/*
**	distribute_memory:
**	this function maps memory; first, it traverses through the tree and tries to
**	find a free space where our new size malloc would fit. If it's positive,
**	reuse_tag will be called, will change tag->size on freespace addres to size
**	and set mapped_size to total previous avaliable free space. If node wasn't found,
**	function uses mmap to create a new map based on the size, then section's tag
**	is inserted with size 'size' and flag USED on freespace. Then I insert new
**	free tag on size + header with full avaliable size without desired 'size
**	with flag FREE. Function returns a pointer pointing at section's tag.
*/

void	distribute_memory(t_malloc *malloc_info)
{
	t_rbnode		*free_tag;
	t_segment_tag	*page_tag;

	if ((malloc_info->mptr = find_free_node(malloc_info)))
	{
		printf("REUSING TAG\n");
		reuse_tag(malloc_info);
	}
	else
	{
		printf("MAPPING...\n");
		map_memory(malloc_info);
		printf("%sMAPPED! %p%s\n", YELLOW, malloc_info->mptr, NORMAL);
		add_next_page(malloc_info);
		printf("PAGE ADDED!\n");
		page_tag = (t_segment_tag *)malloc_info->mptr;
		page_tag->pages = malloc_info->pages;
 		malloc_info->mptr += sizeof(t_segment_tag);
		malloc_info->mapped_size -= sizeof(t_segment_tag); //this and below - fix logic later (add tag_size to size at the beginning)
		if (!(malloc_info->mapped_size > (malloc_info->size + sizeof(t_rbnode) + sizeof(t_rbnode))))
		{
			malloc_info->size = malloc_info->size + (malloc_info->mapped_size - malloc_info->size - sizeof(t_rbnode));
			printf("SIZE CHANGED\n");
		}
			
		insert_tag(malloc_info, malloc_info->mptr - sizeof(t_segment_tag), false);
		malloc_info->mapped_size -= sizeof(t_rbnode);
	}
	printf("STARTING TO ADD A FREE TAG, MPTR: %p\n", malloc_info->mptr);
	free_tag = (t_rbnode *)malloc_info->mptr;
	if (malloc_info->mapped_size > (free_tag->size + sizeof(t_rbnode)))
	{
		size_t idk = malloc_info->size;
		malloc_info->size = malloc_info->mapped_size - free_tag->size - sizeof(t_rbnode);
		insert_tag(malloc_info, free_tag->head, true);
	}
	printf("FREE TAG ADDED!\n");
}


void	*ft_malloc(size_t size)
{
	t_malloc	malloc_info;

	if (size == 0)
		return (NULL);

	printf("%sALL SIZES: t_rbnode %lx | t_segment_tag %lx%s\n", ORANGE, sizeof(t_rbnode), sizeof(t_segment_tag), NORMAL);
	ft_bzero(&malloc_info, sizeof(t_malloc));
	malloc_info.size = size;
	distribute_memory(&malloc_info);
	printf("done with distributing memory!\n");
	// print_tree(g_tags_tree);
	// show_alloc_mem();
	return (malloc_info.mptr += sizeof(t_rbnode));
}

// int main (void)
// {
// 	printf ("tf\n");
// }
	
	int		main(void)
{
	char *ptr;
	char *ptr1;
	char *ptr2 = NULL;

	printf("WE ARE HERE\n");
	ptr = ft_malloc(9);
	ptr2 = ft_malloc(960);
	ptr1 = ft_malloc(11700);
	ptr = ft_malloc(1);
	ptr = ft_malloc(40);
	ptr = ft_malloc(0);
	ptr = ft_malloc(2147483648);
	ptr = ft_malloc(10);
	ptr = ft_malloc(3451);
	ptr = ft_malloc(2200);
	ptr = ft_malloc(3333);
	ptr2 = ft_malloc(3567);
	ptr = ft_malloc(4753);
	ptr = ft_malloc(4294967295);
	ptr = ft_malloc(22344);

	ptr = ft_malloc(3693);
	ptr2 = ft_malloc(3014);
	ptr2 = ft_malloc(2000);
	ptr = ft_malloc(500);
	ptr = ft_malloc(2002);
	ptr = ft_malloc(330);
	ptr = ft_malloc(130);
	ptr = ft_malloc(1112);

	ptr2 = ft_malloc(339);
	ptr = ft_malloc(456);
	ptr = ft_malloc(151);
	ptr = ft_malloc(120);
	ptr = ft_malloc(313);
	ptr = ft_malloc(3693);
	ptr2 = ft_malloc(3014);

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
	ptr = ft_malloc(123423342);
	ptr = ft_malloc(40);
	ptr = ft_malloc(2);
	ptr = ft_malloc(637);
	ptr = ft_malloc(1987839834543);
	ptr = ft_malloc(42);
	ptr = ft_malloc(5);
	ptr = ft_malloc(466);
	ptr2 = ft_malloc(4294967295);
	ptr = ft_malloc(4753);
	ptr = ft_malloc(22234344);
	ptr = ft_malloc(3693);
	ptr2 = ft_malloc(3204);
	ptr2 = ft_malloc(2000);
	ptr = ft_malloc(42949672959999);
	ptr = ft_malloc(2000);
	ptr = ft_malloc(334230);
	ptr = ft_malloc(130);
	ptr = ft_malloc(12);
	ptr2 = ft_malloc(1223414523432);
	ptr = ft_malloc(456);
	ptr = ft_malloc(1);
	ptr = ft_malloc(120);
	ptr = ft_malloc(3124423);
	ptr = ft_malloc(33);
	ptr2 = ft_malloc(3014);
	ptr = ft_malloc(500);
	ptr = ft_malloc(20543433402);
	ptr = ft_malloc(330);
	ptr = ft_malloc(130);
	ptr = ft_malloc(500);
	ptr = ft_malloc(2002);
	ptr = ft_malloc(330);
	ptr = ft_malloc(130);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(120);
	ptr = ft_malloc(3124423);
	ptr = ft_malloc(33);
	ptr2 = ft_malloc(3014);
	ptr = ft_malloc(500);
	ptr = ft_malloc(20543433402);
	ptr = ft_malloc(3332430);
	ptr = ft_malloc(23130);
	ptr = ft_malloc(500234432);
	ptr = ft_malloc(2002);
	ptr = ft_malloc(33423230);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	ptr = ft_malloc(1);
	print_tree(g_tags_tree);
	ptr = strcpy(ptr, "hello");
	ptr2 = strcpy(ptr2, "adam sucks");
	ft_printf("[%s][%s]\n", ptr, ptr2);
	return (0);
}
