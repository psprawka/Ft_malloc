/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:20:50 by psprawka          #+#    #+#             */
/*   Updated: 2018/09/02 00:19:31 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>

#include "libft.h"
#include "defines.h"

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

typedef struct	s_rbnode
{
	char			color_free;
	size_t			size;
	void			*head;
	struct s_rbnode	*parent;
	struct s_rbnode	*left;
	struct s_rbnode	*right;
}				t_rbnode;

extern t_rbnode	*g_tags_tree;

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
** malloc_rotations.c
*/
void		rotate_left(t_rbnode *tag);
void		rotate_right(t_rbnode *tag);

/*
** malloc_tools.c
*/
t_rbnode	*find_position(size_t size);
t_pages		*update_display_info(void *head, long pages, bool ifreturn);
void		count_size(size_t size, t_malloc *malloc_info);
void		show_alloc_mem(void);
void		print_tree(t_rbnode *ptr);

/*
**	page.c
*/
void		add_next_page(t_malloc *malloc_info);

/*
** tree_insertion.c
*/
void		valid_insertion(t_rbnode *root);
void		insertion(t_rbnode *to_insert);

/*
** tree_deletion.c
*/
void		transplant(t_rbnode *to_delete, t_rbnode *to_replace);
void		repair_tree(t_rbnode *to_fix);
t_rbnode	*delete_two_children(t_rbnode *to_delete, char *orgcolor);
void		deletion(t_rbnode *to_delete);

#endif
