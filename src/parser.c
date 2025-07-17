// add header

#include "minishell.h"

// create command node in one go?
t_token_list *move_tokens(t_token *token)
{
    t_token_list *list;
    t_token *current;

    if (!token)
        return (NULL);
    list = list_init();
    list->first = token;
    // print_node(list->first);
    list->size = 1;
    current = list->first->next;
    while (current->next)
    {
        list->size++;
        current = current->next;
    }
    list->size++;
    list->last = current;
    return (list);
}

t_token_list *split_list(t_token_list *list)
{
    t_token *current;
    t_token_list *split_end;

    if (!list || (!list->last)) //modify deleting function, so it will set first and last to token if size == 1
        return (NULL);
    current = list->last;
    while (current)
    {
        if (current->type == PIPE)
        {
            split_end = move_tokens(current->next);
            split_end->first->previous = NULL;
            list->size -= split_end->size;
            list->last = current->previous;
            list->last->next = NULL;
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

// typedef struct s_command {
// 	char *cmnd;
// 	char **args;
// 	t_rdirs **rdirs;
// } t_command;

char    **append_array(char **array, char *str)
{
    char **new_array;
    int  i;

    if (!str)
        return (array);
    if (!array)
    {
        array = malloc(sizeof(char *) * 2);
        array[0] = str;
        array[1] = NULL;
        return (array);
    }
    i = 0;
    while (array[i] != NULL)
        i++;
    new_array = malloc(sizeof(char *) * (i + 2));
    i = -1;
    while (array[++i]) 
        new_array[i] = array[i];
    new_array[i] = str;
    new_array[i + 1] = NULL;
    return (new_array);
}

char **get_args(t_token_list *list)
{
    char **args;
    t_token *current;

    if (!list->first->next)
        return (NULL);
    args = NULL;
    current = list->first->next;
    while (current)
    {
        args = append_array(args, (current->token));
        // printf("no seg\n");
        current = current->next;

    }
    return (args);
}

t_command *parse_command(t_token_list *list)
{
    t_command *command;

    command = malloc(sizeof(t_command));
    if (!command)
        return (NULL);
    command->cmnd = ft_strdup(list->first->token);
    command->rdir_list = get_rdirs(list);
    command->args = get_args(list);
    //free token list
    return (command);
}
void    print_command(t_command *command)
{
    int i;
    t_rdir *current;

    if (!command)
        return ;
    printf("Printing command:\n");
    printf("cmnd: %s\n", command->cmnd);
    printf("args: ");
    i = -1;
    if (command->args)
        while (command->args[++i])
            printf("%s, ", command->args[i]);
    printf("\nrdirs:\n");
    if (command->rdir_list)
    {    
        current = command->rdir_list->first;
        while (current)
        {    
            print_rdir(current);
            current = current->next;
        }  
    }
    printf("\n\n");
}

// right_child = split_list(token_list);
// printf("Left child:\n");
// print_list(token_list);
// printf("\nRight child:\n");
// print_list(right_child);
// printf("size of list: %zu\n", right_child->size);

// t_ast parser(t_token_list *list)
// {
// 	t_ast *ast;
//     t_token_list *right_child;

// 	ast = malloc(sizeof(t_ast));
// 	while (type_in_list(list, PIPE)) //add check for if the list exists?
// 	{
//         ast->type = PIPE_NODE;
//         ast->pipe.right->type = CMND_NODE;
//         right_child = split_list(list);
//         ast->pipe.right = parse_command(right_child);
//         if (type_in_list(list, PIPE))
//             ast = ast->pipe.left;
//         else
//         {
//             ast->pipe.left->type = CMND_NODE;
//             ast->pipe.right = parse_command(list);
//         }
// 	//    ast->pipe.left = li
// 	}
// }
// how do I call it recursivrly?

//add free rdir, free cmnd, free tree functions
// I need to store the root of the tree somehow