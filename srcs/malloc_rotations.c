/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:38:57 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/01 13:39:00 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	rotate_left(t_tag root, t_tag root_parent)
{
	root.parent = root.right;
	root.right.left.parent = root;
	root.right = root.right.left;
	root.parent.left = root;
	root = root.parent;
	root.parent = root_parent;
}

void	rotate_right(t_tag root, t_tag 	root_parent)
{
	root.parent = root.left;
	root.left.right.parent = root;
	root.left = root.left.right;
	root.parent.right = root;
	root = root.parent;
	root.parent = root_parent;
}

