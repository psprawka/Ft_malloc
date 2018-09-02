/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_insertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:27:29 by psprawka          #+#    #+#             */
/*   Updated: 2018/09/02 01:04:58 by psprawka         ###   ########.fr       */
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

void	insertion_case4(t_rbnode *root)
{
	printf("INSERTION root: %p\n", root);
	if (GRANDPA->right && GRANDPA->right->left == root)
	{
		printf("case 1 beg\n");
		rotate_right(PARENT);
		root = root->right;
		printf("case 1 end\n");
	}
	else if (GRANDPA->left && GRANDPA->left->right == root)
	{
		printf("case 2 beg\n");
		rotate_left(PARENT);
		root = root->left;
		printf("case 2 end\n");
	}
	printf("IM HERE\n");
	root == PARENT->left ? rotate_right(GRANDPA) : rotate_left(GRANDPA);
	PARENT->color_free |= BLACK;
	PARENT->color_free &= (BLACK | FREE | USED);
	printf("IM HERE2\n");
	if (!PARENT->parent)
		g_tags_tree = PARENT;
	printf("IM HERE3\n");
	if (PARENT->left != root)
	{
		printf("ONE\n");
		PARENT->left->color_free |= RED;
		PARENT->left->color_free &= (RED | FREE | USED);
		printf("ONE END");
	}
	else
	{
		printf("TWO\n");
		PARENT->right->color_free |= RED;
		PARENT->right->color_free &= (RED | FREE | USED);
		printf("TWO END");
	}
}

void	valid_insertion(t_rbnode *root)
{
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

void	insertion(t_rbnode *to_insert)
{
	t_rbnode	*tptr;
	t_rbnode	*parent;
	
	tptr = g_tags_tree;
	if (tptr == NULL)
		g_tags_tree = to_insert;
	else
	{
		parent = find_position(to_insert->size);
		if (parent->size > to_insert->size)
			parent->left = to_insert;
		else
			parent->right = to_insert;
		to_insert->parent = parent;
	}
	valid_insertion(to_insert);
}
