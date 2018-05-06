/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_insertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:27:29 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/03 12:27:31 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*	Description of functions insertion_case4 and valid_insertion avaliable here
**	https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
**	However in function valid_insertion I examine only three cases:
**		-> 1. Current node is a root of red back tree.
**		-> 3. Parent is red and uncle is red.
**		-> 4. Parent is red and uncle is black.
**	I skip case 2 (Parent is black) because in this case nothing happens - it's
**	goal was to prevent stepping into next if statement (if ... else if). Since
**	my if statement is more detailed than on website above, i don't need it.
*/

void	insertion_case4(t_tag *root)
{
//	ft_printf("case 4\n");
	if (GRANDPA->right && GRANDPA->right->left == root)
	{
		rotate_right(PARENT);
		root = root->right;
	}
	else if (GRANDPA->left && GRANDPA->left->right == root)
	{
		rotate_left(PARENT);
		root = root->left;
	}
	root == PARENT->left ? rotate_right(GRANDPA) : rotate_left(GRANDPA);
	PARENT->color_free |= BLACK;
	PARENT->color_free &= (BLACK | FREE | USED);
	if (!PARENT->parent)
		g_tags_tree = PARENT;
	
	if (PARENT->left != root)
	{
		PARENT->left->color_free |= RED;
		PARENT->left->color_free &= (RED | FREE | USED);
	}
	else
	{
		PARENT->right->color_free |= RED;
		PARENT->right->color_free &= (RED | FREE | USED);
	}
}

void	valid_insertion(t_tag *root)
{
//	if (PARENT && GRANDPA)
//		ft_printf("GRANDPA COLOR: %s\n", (GRANDPA->color_free & RED ? "RED" : (GRANDPA->color_free & BLACK ? "BLACK" : "NONE")));
//	if (PARENT)
//		ft_printf("PAARENT COLOR: %s\n", (PARENT->color_free & RED ? "RED" : (PARENT->color_free & BLACK ? "BLACK" : "NONE")));
	if (!PARENT)
	{
		root->color_free |= BLACK;
		root->color_free &= (BLACK | FREE | USED);
	}
	else if (GRANDPA && (PARENT->color_free & RED) && ((UNCLE_LEFT != PARENT &&
			UNCLE_LEFT && UNCLE_LEFT->color_free & RED) || (UNCLE_RIGHT &&
			UNCLE_RIGHT != PARENT && UNCLE_RIGHT->color_free & RED)))
	{
		if (UNCLE_RIGHT)
		{
			UNCLE_RIGHT->color_free |= BLACK;
			UNCLE_RIGHT->color_free &= (BLACK | FREE | USED);
		}
		if (UNCLE_LEFT)
		{
			UNCLE_LEFT->color_free |= BLACK;
			UNCLE_LEFT->color_free &= (BLACK | FREE | USED);
		}
		GRANDPA->color_free |= RED;
		GRANDPA->color_free &= (RED | FREE | USED);
		valid_insertion(GRANDPA);
	}
	else if (GRANDPA && (PARENT->color_free & RED))
		insertion_case4(root);
}

/*	Insertion:
**	Inseriton is responsible for adding a node to a tree, then validate it based
**	on red black tree's rules. If tree is empty, assing a node. Otherwise find
**	postion to be assigned, thus parent node and add son. Validate insertion.
*/

void	insertion(t_tag *to_insert)
{
	t_tag	*tptr;
	t_tag	*parent;
	
	tptr = g_tags_tree;
	if (tptr == NULL)
		g_tags_tree = to_insert;
	else
	{
		ft_printf("%slooing for a parent%s\n", PINK, NORMAL);
		parent = find_position(to_insert->size);
//		ft_printf("parent found %p %d\n", parent, parent->size);
		if (parent->size > to_insert->size)
		{
//			ft_printf("1\n");
			parent->left = to_insert;
		}
		else
		{
//			ft_printf("2\n");
			parent->right = to_insert;
		}
		to_insert->parent = parent;
	}
//	ft_printf("%svalidate: %d %p\n", BLUE, to_insert->size, to_insert);
//	find_position(785234321);
	valid_insertion(to_insert);
//	ft_printf("%svalidation finished: %s%s\n", ORANGE, (to_insert->color_free & RED ? "RED" : (to_insert->color_free & BLACK ? "BLACK" : "NONE")), NORMAL);
}
