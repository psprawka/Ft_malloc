/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 20:51:01 by psprawka          #+#    #+#             */
/*   Updated: 2018/09/01 20:51:33 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define TINY	128
# define SMALL	1024

# define IS_TINY(x)		x > 0 && x < TINY ? 1 : 0
# define IS_SMALL(x)	x >= TINY && x < SMALL ? 1 : 0

# define BLACK	1
# define RED	2
# define FREE	4
# define USED	8

# define GRANDPA		root->parent->parent
# define PARENT			root->parent
# define UNCLE_LEFT		GRANDPA->left
# define UNCLE_RIGHT	GRANDPA->right

#endif
