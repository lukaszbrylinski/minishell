// add header

#include "minishell.h"

t_tree_node *create_node(t_token *token, t_tree_node *left, t_tree_node *right)
{
	t_tree_node *node;

	node = malloc(sizeof(t_tree_node));
	node->token = token->token;
	node->left = left;
	node->right;
	return (node);
}