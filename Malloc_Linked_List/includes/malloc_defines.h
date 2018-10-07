/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_defines.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 20:51:01 by psprawka          #+#    #+#             */
/*   Updated: 2018/10/07 14:23:33 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_DEFINES_H
# define MALLOC_DEFINES_H

# define TINY	128
# define SMALL	1024

# define IS_TINY(x)		x > 0 && x < TINY ? 1 : 0
# define IS_SMALL(x)	x >= TINY && x < SMALL ? 1 : 0

# define FREE	0
# define USED	1

#endif
