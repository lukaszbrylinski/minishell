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

// t_ast	*create_pipe_node(t_ast *left, t_ast *right)
// {
// 	t_ast	*node;

// 	node = malloc(sizeof(t_ast));
// 	if (!node)
// 		return (NULL);
// 	node->type = PIPE_NODE;
// 	node->pipe.left = left;
// 	node->pipe.right = right;
// 	return (node);
// }

t_token_list *wrap_sublist(t_token *start, t_token *end, t_token_list *list)
{
	//t_token_list *list;
	t_token *curr;

	if (!start || !end)
		return NULL;
	//list = malloc(sizeof(t_token_list));
	// if (!list)
	// 	return NULL;
	// list->first = start;
	// list->last = end;
	// list->size = 0;

	curr = start;
	while (curr)
	{
		list->size++;
		if (curr == end)
			break;
		if (curr->next == NULL) // safety stop
			break;
		curr = curr->next;
	}
	return (list);
}

// t_ast *parse_tokens(t_token *start, t_token *end, t_token_list *list)
// {
// 	t_token *curr;
// 	t_command		*cmd;
// 	//t_token_list	*sublist;
// 	// warunki zabezpieczające przed nieskończoną rekurencją
// 	if (!start || !end || start == end->next || start == end)
// 		return NULL;

// 	curr = end;
// 	if (curr && curr != start)
// 	{
// 		if (curr->type == PIPE)
// 		{
// 			t_ast *node = ft_calloc(1, sizeof(t_ast));
// 			if (!node)
// 				return NULL;

// 			node->type = PIPE_NODE;

// 			// ważne: zachowujemy przedział
// 			node->pipe.left = parse_tokens(start, curr->previous, list);
// 			node->pipe.right = parse_tokens(curr->next, end, list);

// 			return node;
// 		}
// 		curr = curr->previous;
// 	}

// 	// jeśli nie znaleziono pipe’a, zbuduj pojedyncze polecenie
// 	// t_token_list *sublist = wrap_sublist(start, end);
// 	// if (!sublist)
// 	// 	return NULL;

// 	// return parse_command(sublist);
// 	list = wrap_sublist(start, end, list);
// 	cmd = parse_command(list);
// 	//list_del_free(sublist);
// 	return (create_cmd_node(cmd));
// }

t_ast *parse_tokens(t_token *start, t_token *end, t_token_list *list)
{
	t_token *curr;
	t_command		*cmd;
	//t_token_list	*sublist;
	// warunki zabezpieczające przed nieskończoną rekurencją
	if (!start || !end || start == end->next || start == end)
		return NULL;

	curr = end;
	if (curr && curr != start)
	{
		if (curr->type == PIPE)
		{
			t_ast *node = ft_calloc(1, sizeof(t_ast));
			if (!node)
				return NULL;

			node->type = PIPE_NODE;

			// ważne: zachowujemy przedział
			node->pipe.left = parse_tokens(start, curr->previous, list);
			node->pipe.right = parse_tokens(curr->next, end, list);

			return node;
		}
		curr = curr->previous;
	}

	// jeśli nie znaleziono pipe’a, zbuduj pojedyncze polecenie
	// t_token_list *sublist = wrap_sublist(start, end);
	// if (!sublist)
	// 	return NULL;

	// return parse_command(sublist);
	list = wrap_sublist(start, end, list);
	cmd = parse_command(list);
	//list_del_free(sublist);
	return (create_cmd_node(cmd));
}

t_ast *build_ast(t_token_list *tokens)
{
	t_ast *ast;

	if (!tokens || !tokens->first)
		return (NULL);
	// debug_print_tokens(tokens->first);
	ast = parse_tokens(tokens->first, tokens->last, tokens);
	//list_del_free(tokens); // <-- zwalniamy dopiero po całym parsowaniu
	return (ast);
}

void    print_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == PIPE)
	{	
		print_ast(ast->pipe.left);
		print_ast(ast->pipe.right);
	}
    print_command(ast->cmnd);
}