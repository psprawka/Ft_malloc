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

t_tag	*g_tags_tree = NULL;


/*
**	Traverse_tree:
**	this tool takes a desired size and finds the most appropiate node that would
**	fit new malloc. Function goes till the end of a tree, but may break before
**	hitting the end. When size is the same, it returns a curreny node, if malloc
**	size is bigger than node size, we're moving on the right outer branch of
**	the tree until we find a proper node. If node big enoungh doesn't exist,
**	return null. When size is less than node size, function checks next left
**	node and copares size. If size is still less than node size, it moves to
**	left child, otherwise current node is returned.
*/

void	*traverse_tree(size_t size)
{
	t_tag	*tptr;
	
	tptr = g_tags_tree;
	while (tptr)
	{
		if (tptr->size == size)
			return ((void *)tptr);
		else if (tptr->size > size)
		{
			if (tptr->left && tptr->left->size > size)
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

void	*map_memory(size_t size)
{
	void	*freespace;
	t_tag	*free_tag;
	int		mapped;

	if ((freespace = traverse_tree(size)) != NULL)
		reuse_tag(freespace, size, *mapped);
	else
	{
		if (IS_TINY(size) && (mapped = 100 * TINY) > -1)
			freespace = mmap(NULL, 100 * TINY, MAP_ANONYMOUS,
				PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, -1, 0);
		else if (IS_SMALL(size) && (mapped = 100 * SMALL))
			freespace = mmap(NULL, 100 * SMALL, MAP_ANONYMOUS,
				PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, -1, 0);
		else if (mapped = size)
			freespace = mmap(NULL, size, MAP_ANONYMOUS,
							 PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, -1, 0);
 		freespace += sizeof(t_page_tag);
		insert_tag(freespace, freespace - sizeof(t_page_tag), size, false);
	}
	free_tag = (t_tag *)freespace
	insert_tag(freespace + sizeof(t_tag) + free_tag->size, free_tag->head,
			   mapped - free_tag->size, true);
	return (freespace);
}


void	*ft_malloc(size_t size)
{
	void *mptr;
	
	mptr = map_memory(size);
	
	
	
	return (NULL);
}


int		main(void)
{
	char *ptr;
	ptr = ft_malloc(10);
	return (0);
}
