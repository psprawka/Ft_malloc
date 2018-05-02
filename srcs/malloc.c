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




void	*traverse_tree(size_t size)
{
	void	*freenode;
	t_tag	*tptr;
	
	freenode = NULL;
	tptr = g_tags_tree;
	while (tptr)
	{
		if (tptr->size == size)
			return (tptr);
		else if (tptr->size > size)
		{
			if (tptr->left && tptr->left->size > size)
				tptr = tptr->left;
			else
				return (ptr);
		}
		else
		{
			if (tptr->right)
				tptr = tptr->right;
			else
				return (NULL);
		}
	}
	return (freenode);
}

void	*map_memory(size_t size)
{
	void	*freespace;

	if ((freespace = traverse_tree(size)) != NULL)
		return (freespace);
	else
	{
		if (IS_TINY(size))
			freespace = mmap(NULL, 100 * TINY, MAP_ANONYMOUS,
				PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, -1, 0);
		else if (IS_SMALL(size))
			freespace = mmap(NULL, 100 * SMALL, MAP_ANONYMOUS,
				PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, -1, 0);
		else
			freespace = mmap(NULL, size, MAP_ANONYMOUS,
							 PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, -1, 0);
		add_page_metadata(freespace);
		freespace += sizeof(t_page_meta);
	}
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
