// add header

#include "minishell.h"

// create command node in one go?
t_token_list *move_tokens(t_token *token) // no list to print - why?
{
    t_token_list *list;
    t_token *current;

    if (!token)
		return (NULL);
	// else if (!token->next)
	// 	return (NULL); //change for error handling (missing target)
    list = list_init();
    list->first = token;
	list->first->previous = NULL;
    // print_node(list->first);
    list->size = 1;
    current = list->first->next;
    while (current)
    {
        list->size++;
        current = current->next;
    }
    // list->size++;
    list->last = current;
    return (list);
}

t_token_list *split_list(t_token_list *list) // check size
{
    t_token *current;
    t_token_list *split_end;

    if (!list || (!list->last)){ //modify deleting function, so it will set first and last to token if size == 1
		return (NULL);
	}
    current = list->last;
    while (current)
    {
        if (current->type == PIPE)
        {
            split_end = move_tokens(current->next);
            // list->size -= split_end->size; /seg fault
			// printf("list size changed, no seg\n");
            list->last = current->previous;
            list->last->next = NULL;
			free_token(current);
            return (split_end);
        }
        current = current->previous;
    }
    return (NULL);
}

// modify so it will substract size of new list form the old one
//memory addres of the node I want to split? or I can just look for the first pipe

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

t_ast *create_cmnd_node(t_token_list *list)
{
	t_ast *cmnd_node;
	t_command *command;

	if (!list)
		return (NULL);
	cmnd_node = malloc(sizeof(t_ast));
	if (!cmnd_node)
		return (NULL); //no need for error handling at this point
	cmnd_node->type = CMND_NODE;
	command = parse_command(list);
	if (!command)
		return (free_ast(cmnd_node), NULL); //error handling for cmnd_node
	cmnd_node->cmnd = command;
	// printf("no seg\n");
	return (cmnd_node);
}

t_ast *create_pipe_node(t_token_list *list)
{
	t_ast *cmnd_node;
	t_ast *pipe_node;
	t_token_list *split_end;

	if (!list)
		return (NULL);
	if (type_in_list(list, PIPE)) // changed to check if pipe in list. If pipe in list parsing with pipe
	{
		split_end = split_list(list);
		if (!split_end)
			return (NULL); //change to error handling}
		pipe_node = malloc(sizeof(t_ast));
		if (!pipe_node)
			return (list_del_free(split_end), NULL);// changed to free
		pipe_node->type = PIPE_NODE;
		cmnd_node = create_cmnd_node(split_end);
		pipe_node->pipe.right = cmnd_node;
		if (type_in_list(list, PIPE))
			pipe_node->pipe.left = NULL;
		else
			pipe_node->pipe.left = create_cmnd_node(list); //move to create cmnd node, so we dont have to free the mail list
		return (list_del_free(split_end), pipe_node);
	}
	else
		return (create_cmnd_node(list));
}

void	print_pipe_node(t_ast *node)
{
	printf("printing node:\n");
	if (!node)
		printf("no node to print\n");
	printf("node type: %d\n", node->type);
	if (node->pipe.right)
	{
		printf("printing right child type: %d\n", node->pipe.right->type);
		if (node->pipe.right->type == CMND_NODE)
			print_command(node->pipe.right->cmnd);
		else
			printf("pipe node: right %p, left %p\n", node->pipe.right->pipe.right, node->pipe.right->pipe.left);
	}
	if (node->pipe.left)
	{
		printf("printing left child type: %d\n", node->pipe.left->type);
		if (node->pipe.left->type == CMND_NODE)
			print_command(node->pipe.left->cmnd);
		else
			printf("pipe node: right %p, left %p\n", node->pipe.left->pipe.right, node->pipe.left->pipe.left);
	}
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
