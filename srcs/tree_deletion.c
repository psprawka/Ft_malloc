/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_deletion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:38:35 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/04 10:38:37 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

#define BROTHER right_son->parent->right
#define	PARENTT right_son->parent

void	repair_tree(t_tag *right_son)
{
	char	parent_color;
	char	son_color;

	if (!right_son || !PARENTT)
		return ;
	printf("not return %p %zu %p %p\n", right_son, right_son->size, right_son->left, right_son->right);
	if (BROTHER->color_free & RED)
	{
		printf("case 1\n");
		parent_color = PARENTT->color_free & RED ? RED : BLACK;
		son_color = BROTHER->color_free & RED ? RED : BLACK;
		PARENTT->color_free |= son_color;
		PARENTT->color_free &= (son_color | FREE | USED);
		BROTHER->color_free |= parent_color;
		BROTHER->color_free &= (parent_color | FREE | USED);
		rotate_left(PARENTT);
	}
	printf("here 2\n");
	if (BROTHER->color_free & BLACK && (!BROTHER->left || BROTHER->left->color_free & BLACK) && (!BROTHER->right || BROTHER->right->color_free & BLACK))
	{
		printf("case 2\n");
		BROTHER->color_free |= RED;
		BROTHER->color_free |= (RED | FREE | USED);
		PARENTT->color_free |= BLACK;
		if (right_son->color_free & RED)
			right_son->color_free &= (RED | USED | FREE);
		repair_tree(PARENTT);
	}
	printf("here 3\n");
	if (BROTHER->color_free & BLACK && (BROTHER->left->color_free & RED) && (BROTHER->right || BROTHER->right->color_free & BLACK))
	{
		printf("case 3\n");
		parent_color = BROTHER->color_free & RED ? RED : BLACK;
		son_color = BROTHER->left->color_free & RED ? RED : BLACK;
		BROTHER->color_free |= son_color;
		BROTHER->color_free &= (son_color | FREE | USED);
		BROTHER->left->color_free |= parent_color;
		BROTHER->color_free &= (parent_color | FREE | USED);
		rotate_right(BROTHER);
	}
	printf("here 3\n");
	if (BROTHER->color_free & BLACK && BROTHER->right->color_free & RED)
	{
		printf("case 4\n");
		parent_color = PARENTT->color_free & RED ? RED : BLACK;
		BROTHER->color_free |= parent_color;
		BROTHER->color_free &= (parent_color | FREE | USED);
		PARENTT->color_free |= BLACK;
		PARENTT->color_free &= (BLACK | FREE | USED);
		rotate_left(PARENTT);
		if (PARENTT->parent->right)
		{
			PARENTT->parent->right->color_free |= BLACK;
			PARENTT->parent->right->color_free &= (BLACK | FREE | USED);
		}
		if (right_son->color_free & RED)
			right_son->color_free &= (RED | USED | FREE);
	}
}


void	delete_two_children(t_tag *to_delete)
{
	t_tag	*to_replace;
	char	color;
	char	successor_color;

	color = to_delete->color_free & RED ? RED : BLACK;
	
	if (!to_delete->right->left)
	{
		printf("deletion: third case\n");
		if (!to_delete->parent)
			g_tags_tree = to_delete->right;
		else if (to_delete->parent->right == to_delete)
			to_delete->parent->right = to_delete->right;
		else if (to_delete->parent->left == to_delete)
			to_delete->parent->left = to_delete->right;
		to_delete->right->parent = to_delete->parent;
		to_delete->right->left = to_delete->left;
		successor_color = to_delete->right->color_free & RED ? RED : BLACK;
		to_delete->right->color_free |= color;
		to_delete->right->color_free &= (color | FREE | USED);
		to_delete->left->parent = to_delete->right;
//		printf("before repair\n");
//		print_tree(g_tags_tree);
//		printf("before rsfdfdsdfepair\n");
		if (to_delete->right && to_delete->right->right)
		{
//			printf("before sadsadsarsfdgdsdgsdgrefdscxeffsepair\n");
			to_delete->right->right->color_free |= BLACK;
			to_delete->right->right->color_free &= (BLACK | FREE | USED);
		}
//		else if (to_delete->left->left || to_delete->left->right)
//		{
//			printf("feuh\n");
//			valid_insertion(to_delete->left->left ? to_delete->left->left : to_delete->left->right);
//		}
		if (successor_color & BLACK)
//		{
//			printf("before sadsadsarsfdgdsdgsdffsepair %p\n", to_delete->right->right);
			repair_tree(to_delete->right->right);
//			printf("before sadsadsfgbfgdsdwdbarepair\n");
//		}
	}
	else
	{
		printf("deletion: forth case %zu\n", to_delete->size);
		to_replace = to_delete->right->left;
		while (to_replace->left)
			to_replace = to_replace->left;
		printf("replace %zu %p %p\n", to_replace->size, to_replace->left, to_replace->right);
		to_replace->parent->left = to_replace->right;
		if (to_replace->right)
		{
			to_replace->right->parent = to_replace->parent;
			to_replace->right->color_free |= BLACK;
		}
		to_replace->left = to_delete->left;
		to_delete->left->parent = to_replace;
		to_replace->right = to_delete->right;
		to_delete->right->parent = to_replace;
		to_replace->parent = to_delete->parent;
		successor_color = to_replace->color_free & RED ? RED : BLACK;
		to_replace->color_free |= color;
		to_replace->color_free &= (color | USED | FREE);
		printf("here too\n");
		if (!to_delete->parent)
			g_tags_tree = to_replace;
		printf("here too\n");
		if (successor_color & BLACK)
			repair_tree(to_replace->right);
		printf("here too\n");
	}
}

void	delete_one_child(t_tag *to_delete)
{
	if (!to_delete->left && to_delete->right)
	{
		printf("deletion: second case 1\n");
		if (!to_delete->parent)
			g_tags_tree = to_delete->right;
		else if (to_delete->parent->right == to_delete)
			to_delete->parent->right = to_delete->right;
		else if (to_delete->parent->left == to_delete)
			to_delete->parent->left = to_delete->right;
		to_delete->right->parent = to_delete->parent;
		to_delete->right->color_free |= BLACK;
		to_delete->right->color_free &= (BLACK | FREE | USED);
	}
	else if (to_delete->left && !to_delete->right)
	{
		printf("deletion: second case 2\n");
		if (!to_delete->parent)
			g_tags_tree = to_delete->left;
		else if (to_delete->parent->right == to_delete)
			to_delete->parent->right = to_delete->left;
		else if (to_delete->parent->left == to_delete)
			to_delete->parent->left = to_delete->left;
		to_delete->left->parent = to_delete->parent;
		to_delete->left->color_free |= BLACK;
		to_delete->left->color_free &= (BLACK | FREE | USED);
	}
}

void	deletion(t_tag *to_delete)
{
	if (!to_delete->left && !to_delete->right)
	{
		printf("deletion: first case\n");
		if (!to_delete->parent)
			g_tags_tree = NULL;
		else if (to_delete->parent->right == to_delete)
			to_delete->parent->right = NULL;
		else if (to_delete->parent->left == to_delete)
			to_delete->parent->left = NULL;
	}
	else if ((!to_delete->left && to_delete->right) ||
			 (to_delete->left && !to_delete->right))
		delete_one_child(to_delete);
	else if (to_delete->left && to_delete->right)
		delete_two_children(to_delete);
}
