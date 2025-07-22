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
	// t_token *temp;
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

// right_child = split_list(token_list);
// printf("Left child:\n");
// print_list(token_list);
// printf("\nRight child:\n");
// print_list(right_child);
// printf("size of list: %zu\n", right_child->size);

t_ast *create_cmnd_node(t_token_list *list)
{
	t_ast *cmnd_node;
	t_command *command;

	if (!list)
		return (NULL);
	cmnd_node = malloc(sizeof(t_ast));
	if (!cmnd_node)
		return (NULL); //error handling
	cmnd_node->type = CMND_NODE;
	command = parse_command(list);
	if (!command)
		return (NULL); //error handling
	cmnd_node->cmnd = command;
	// printf("no seg\n");
	return (cmnd_node);
}

t_ast *create_pipe_node(t_token_list *list)
{
	t_ast *cmnd_node;
	t_ast *pipe_node;
	t_token_list *split_end;

	printf("List: \n");
	print_list(list);
	if (!list)
		return (NULL);
	split_end = split_list(list); //seg fault
	if (!split_end)
		return (NULL); //change to error handling}
	printf("Split end: \n");
	print_list(split_end);
	pipe_node = malloc(sizeof(t_ast));
	if (!pipe_node)
		return (NULL); //error handling
	// printf("pipe node alloced, no seg\n");
	pipe_node->type = PIPE_NODE;
	cmnd_node = create_cmnd_node(split_end);
	// pipe_node->pipe.right->type = CMND_NODE;
	pipe_node->pipe.right = cmnd_node;
	// pipe_node->pipe.right = malloc(sizeof(t_ast));
	//
	// pipe_node->pipe.right->type = CMND_NODE;
	// pipe_node->pipe.right = parse_command(split_end);
	if (type_in_list(list, PIPE))
		pipe_node->pipe.left = NULL;
	else
		pipe_node->pipe.left = create_cmnd_node(list);
	// current = list->last;
	// while (current && current->type != PIPE)
	// 	current = current->previous;
	// list->last = current->previous;
	// list->last->next = NULL;
	//substract from size
	// free_token(current);
	list_del_free(split_end); //move to create cmnd node, so we dont have to free the mail list
	// printf("no seg\n");
	return (pipe_node);
}

void	print_pipe_node(t_ast *node)
{
	printf("printing node:\n");
	if (!node)
		printf("no node to print\n");
	printf("node type: %d\n", node->type);
	if (node->pipe.right)
	{	printf("printing right child type: %d\n", node->pipe.right->type);
		if (node->pipe.right->type == CMND_NODE)
			print_command(node->pipe.right->cmnd);
		else
			printf("pipe node: right %p, left %p\n", node->pipe.right->pipe.right, node->pipe.right->pipe.left);}
	if (node->pipe.left)
	{	printf("printing left child type: %d\n", node->pipe.left->type);
		if (node->pipe.left->type == CMND_NODE)
			print_command(node->pipe.left->cmnd);
		else
			printf("pipe node: right %p, left %p\n", node->pipe.left->pipe.right, node->pipe.left->pipe.left);}
}

t_ast *parser(t_token_list *list)
{
    t_ast *root;
	t_ast *current;

	if (!list)
		return (NULL);
	root = create_pipe_node(list);
	print_pipe_node(root);
	// printf("root: %p", current->pipe.left);
	current = root;
	printf("current: %p\n", current);
	while (list && type_in_list(list, PIPE))
	{
		printf("creating pipe node\n");
		printf("current->pipe.left: %p\n", current->pipe.left);
		current->pipe.left = create_pipe_node(list);
		printf("new pipe node:\n");
		print_pipe_node(current->pipe.left);
		if (!current->pipe.left)
			return (NULL); // or some cleanup
		current = current->pipe.left;
		printf("one pipe node created!\n");
	}
	printf("ast created\n");
	return (root);
}

// t_ast *parser(t_token_list *list)
// {
//     t_ast *root;
// 	t_ast *current;
// 	// t_token *token;
//     t_token_list *right_child;

// 	root = malloc(sizeof(t_ast));
//     if (!root)
//         return (NULL);
//     current = root;
// 	while (type_in_list(list, PIPE)) //add check for if the list exists?
// 	{
//         current->type = PIPE_NODE;
// 		printf("no seg after assigning type as pipe node\n");
//         current->pipe.right = malloc(sizeof(t_ast));
// 		printf("no seg after allocing pipe.right\n");
// 		if (!current->pipe.right)
// 			return (NULL);
//         current->pipe.right->type = CMND_NODE;
// 		printf("no seg after assigning pipe right type as pipe node\n");
//         right_child = split_list(list);
// 		print_list(right_child);
// 		printf("no seg splitting token list\n");
//         current->pipe.right->cmnd = parse_command(right_child);
// 		print_command(current->pipe.right->cmnd);
// 		printf("no seg splitting token list\n");
//         if (type_in_list(list, PIPE))
//         {
//             current->pipe.left = malloc(sizeof(t_ast));
//             current = current->pipe.left;
//         }
//         else
//         {
//             current->pipe.left = malloc(sizeof(t_ast));
//             current->pipe.left->type = CMND_NODE;
//             current->pipe.left->cmnd = parse_command(list);
//         }
// 	//    ast->pipe.left = li
// 	}
//     return (root);
// }

// void    print_ast(t_ast *ast)
// {
//     if (!ast)
//         return ;
//     if (ast->pipe.left)
//         print_ast(ast->pipe.left);
//     else if (ast->pipe.right)
//         print_ast(ast->pipe.right);
//     print_command(ast->cmnd);
// }
// how do I call it recursivrly?

//add free rdir, free tree functions
// I need to store the root of the tree somehow