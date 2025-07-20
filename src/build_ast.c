#include "minishell.h"

t_ast	*create_cmd_node(t_command *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = CMND_NODE;
	node->cmnd = cmd;
	return (node);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = PIPE_NODE;
	node->pipe.left = left;
	node->pipe.right = right;
	return (node);
}