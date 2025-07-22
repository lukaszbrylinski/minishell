#include "minishell.h"


void    print_ast(t_ast *ast)
{
	if (!ast)
		return ;
	printf("printing ast\n");
	// print_pipe_node(ast);
	if (ast->type == CMND_NODE)
		printf("just one command\n");
	while (ast->type != CMND_NODE)
	{
		print_pipe_node(ast);
		ast = ast->pipe.left;
	}
}
void free_ast(t_ast *node)
{
	if (!node)
		return;

	if (node->type == CMND_NODE)
		free_command(node->cmnd);
	else if (node->type == PIPE_NODE)
	{
		free_ast(node->pipe.left);
		free_ast(node->pipe.right);
	}
	free(node);
}