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



void *ft_malloc(size_t size)
{
	void *mptr;
	
//	mptr = mmap(NULL, )
	ft_printf("%d\n", getpagesize());
	
	
	
	return (NULL);
}


int main(void)
{
	char *ptr;
	ptr = ft_malloc(10);
	return (0);
}
