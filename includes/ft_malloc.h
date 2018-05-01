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

# define TINY	128
# define SMALL	1024

# define IS_TINY(x)		x > 0 && x < TINY ? 1 : 0
# define IS_SMALL(x)	x => TINY && x < LARGE ? 1 : 0
# define IS_LARGE(x)	x => LARGE ? 1 : 0

# define BLACK	'b'
# define RED	'r'

typedef struct	s_rbtree
{
	char			color;
	short			size;
	void			*mptr;
	struct s_rbtree	*parent;
	struct s_rbtree	*left;
	struct s_rbtree	*right;
}				t_rbtree;


/*
** free.c
*/
void ft_free(void *ptr);

/*
** malloc.c
*/
void *ft_malloc(size_t size);
//void *ft_realloc(void *ptr, size_t size);

/*
 ** malloc_rbtrees.c
 */
void	rotation_left(t_rbtree *root, t_rbtree *root_parent);
void	rotation_right(t_rbtree *root, t_rbtree *root_parent);

#endif
