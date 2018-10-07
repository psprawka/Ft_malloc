/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:20:50 by psprawka          #+#    #+#             */
/*   Updated: 2018/10/07 14:51:46 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

// #include "libft.h"
#include "malloc_defines.h"

typedef struct	s_malloc
{
	size_t			size;
	size_t			mapped_size;
	int64_t			pages;
	void			*mptr;
}				t_malloc;

typedef struct	s_pages
{
	long			pages_nb;
	void			*head;
}				t_pages;

typedef struct	s_segment_tag 
{
	short			to_free;
	long			pages;
	void			*nextpage;
}				t_segment_tag;

/*
** free.c
*/
void 		ft_free(void *ptr);

/*
** malloc.c
*/
void		*find_free_node(t_malloc *malloc_info);
void		map_memory(t_malloc *malloc_info);
void		*ft_malloc(size_t size);

/*
** malloc_tags.c
*/
void		insert_tag(t_malloc *malloc_info, void *head, bool if_free);
void		reuse_tag(t_malloc *malloc_info);


/*
** malloc_tools.c
*/
t_pages		*update_display_info(void *head, long pages, bool ifreturn);
void		count_size(size_t size, t_malloc *malloc_info);
void		show_alloc_mem(void);

/*
**	page.c
*/
void		add_next_page(t_malloc *malloc_info);


#endif
