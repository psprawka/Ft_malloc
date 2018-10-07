/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 21:18:25 by psprawka          #+#    #+#             */
/*   Updated: 2018/10/07 14:25:15 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	add_next_page(t_malloc *malloc_info)
{
	t_pages			*info;
	t_segment_tag	*page_tag;

	info = update_display_info(NULL, 0, 1);
	if (!info->head)
	{
		update_display_info(malloc_info->mptr, 0, 0);
		return ;
	}
	page_tag = (t_segment_tag *)info->head;
	while (page_tag->nextpage)
		page_tag = (t_segment_tag *)(page_tag->nextpage);
	page_tag->nextpage = malloc_info->mptr;
}
