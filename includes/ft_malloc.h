/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:20:50 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/30 16:20:54 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include <sys/mman.h>

# define TINY	128
# define SMALL	1024

# define IS_TINY(x)		x > 0 && x < TINY ? 1 : 0
# define IS_SMALL(x)	x >= TINY && x < SMALL ? 1 : 0

# define BLACK	1
# define RED	2
# define FREE	5
# define USED	6

#define GRANDPA		root->parent->parent
#define PARENT		root->parent
#define UNCLE_LEFT	GRANDPA->left
#define UNCLE_RIGHT	GRANDPA->right



typedef struct	s_page_tag
{
	short			size;
}				t_page_tag;


typedef struct	s_tag
{
	char			color_free;
	int				size;
	void			*head;
	struct s_tag	*parent;
	struct s_tag	*left;
	struct s_tag	*right;
}				t_tag;


extern t_tag	*g_tags_tree;


/*
** free.c
*/
void ft_free(void *ptr);

/*
** malloc.c
*/
void	*find_free_node(size_t size);
void	*map_memory(size_t size);
void	*ft_malloc(size_t size);

/*
** malloc_tags.c
*/
void	insert_tag(void *mptr, void *head, size_t size, bool if_free);
void	reuse_tag(void *mptr, int size, int *remainder);

/*
** malloc_rotations.c
*/
void	rotate_left(t_tag *tag);
void	rotate_right(t_tag *tag);

/*
** malloc_tools.c
*/
t_tag	*find_position(size_t size);

/*
** tree_insertion.c
*/
void	valid_insertion(t_tag *root);
void	insertion(t_tag *to_insert);

#endif
