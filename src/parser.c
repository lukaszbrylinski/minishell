// add header

#include "minishell.h"

int	type_in_list(t_token_list *list, t_type type)
{
	t_token *current;
	if (!list || !list->first)
		return (0);
	current = list->first;
	while (current)
	{
		if (current->type == type)
			return (1);
		current = current->next;
	}
	return (0);
}

t_ast *parser(t_token_list *list)
{
    t_ast *root;
	t_ast *current;

	if (!list)
		return (NULL);
	root = create_pipe_node(list);
	//print_pipe_node(root);
	current = root;
	while (list && type_in_list(list, PIPE))
	{
		current->pipe.left = create_pipe_node(list);
		//print_pipe_node(current->pipe.left);
		if (!current->pipe.left)
			return (NULL); // error handling
		current = current->pipe.left;
	}
	//free list
	return (root);
}

void	print_ast(t_ast *ast) //correct?
{
	if (!ast)
		return ;
	printf("printing ast\n");
	if (ast->type == CMND_NODE)
	{	
		printf("just one command\n");
		print_command(ast->cmnd);
		return ;
	}
	else
		while (ast->type != CMND_NODE)
		{
			print_pipe_node(ast);
			ast = ast->pipe.left;
		}
}
void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == CMND_NODE)
		free_command(node->cmnd);
	else if (node->type == PIPE_NODE)
	{
		free_ast(node->pipe.left);
		free_ast(node->pipe.right);
	}
	free(node);
}
