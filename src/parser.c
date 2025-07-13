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
// 	char *args;
// 	t_rdirs **rdirs;
// } t_command;

size_t  getlen_2d(t_rdir **rdirs)
{
    size_t  i;

    i = 0;
    while(rdirs && rdirs[i])
        i++;
    return (i);
}

void    free_rdirs(t_rdir **rdirs)
{
    int i;

    if (!rdirs)
        return ;
    i = -1;
    while (rdirs[++i])
    {
        if (rdirs[i]->target)
            free(rdirs[i]->target);
        free(rdirs[i]);
    }
    free(rdirs);
}

t_rdir **append_2d(t_rdir **rdirs, t_rdir *rdir)
{
    t_rdir **joined;
    int i;

    if (!rdir && !rdirs)
        return (NULL);
    joined = malloc(sizeof(t_rdir *) * (getlen_2d(rdirs) + 2));
    i = -1;
    while (rdirs && rdirs[++i])
        joined[i] = rdirs[i];
    joined[i] = rdir;
    joined[++i] = NULL;
    free(rdirs); //check if it won't affect singular rdirs
    return (joined);
}

// typedef struct s_rdir {
// 	int fd;
// 	char *target;
// 	int	type; //RDIR_IN, RDIR_OUT, RDIR_APPEND etc.
// } t_rdirs;

// Shell redirection allows you to change where a command gets its input or sends its output. Instead of the default input (keyboard) and output (terminal), you can redirect input from or output to files, or even to other commands. The main redirection operators are > (output redirection), >> (output redirection with appending), and < (input redirection). 
// Here's a breakdown of the common redirection types:
// 1. Output Redirection (>):
// command > file: Redirects the standard output of command to file. If file exists, its contents are overwritten. If it doesn't exist, it's created. 
// command >| file: Similar to > but overwrites the file even if the shell is configured to prevent overwrites. 
// command 2> file: Redirects the standard error (error messages) of command to file. 
// command > file 2>&1: Redirects both standard output and standard error to file. 
// command &> file: Another way to redirect both standard output and standard error to file. 
// 2. Appending Output Redirection (>>):
// command >> file: Redirects the standard output of command to file and appends the output to the end of the file. If the file doesn't exist, it's created. 
// 3. Input Redirection (<):
// command < file: Redirects the contents of file to be used as standard input for command. 
// 4. Piping (|):
// command1 | command2: Redirects the standard output of command1 to be the standard input of command2. This allows you to chain commands together, where the output of one becomes the input of the next. 
// 5. File Descriptor Redirection:
// n > file: Redirects file descriptor n to file.
// n >> file: Appends output from file descriptor n to file.
// n < file: Reads from file as file descriptor n. 

// Implement redirections:
// ◦ < should redirect input.
// ◦ > should redirect output.
// ◦ << should be given a delimiter, then read the input until a line containing the
// delimiter is seen. However, it doesn’t have to update the history!
// ◦ >> should redirect output in append mode.

// possible redirections: 
// < << > >> 
// <> 2> 2>&1 1>&2 &> 2>>, &>>
// <<< (herestring), <<-, <(cmd), >(cmd)
// n<&m n>&m would only work with exec

t_rdir_type get_rdir_type(t_token *token)
{
    t_rdir_type type;

    type = 0;
    if (ft_strlen(token->token) == 2)
    {   
        if (token->token[0] == token->token[1])
        {
            if (token->token[0] == '<')
                type = HDOC;
            else
                type = AEND;
        }
        // else
        //     type = <> (read and write);
    }
    else
    {   
        if (token->token[0] == '<')
            type = IN;
        else
            type = OUT;
    }
    return (type);
}

// TO DO: heredoc
// t_rdir *create_rdir(t_token_list *list)
// {
//     t_rdir  *rdir;
//     t_token *current;
//     t_rdir_type type;
    
//     if (!list || !list->last)
//         return (NULL);
//     current = list->last;
//     while (current)
//     {
//         if (current->type == RDIR)
//             rdir = malloc(sizeof(rdir));
//     }
    

//     // I need to iterate from behind until I find rdir
//     // I will check the exact rdir type
//     // parse specified tokens to rdir (extract the file based on type)
//     // should I check if the file can be opened?
// }

// I need to add one more star to modify it (?)
// t_rdir **get_rdirs(t_token_list *list, t_rdir ***rdirs, int i) 
// {
//     t_rdir *rdirs;
//     int i;

//     rdirs = NULL;
//     i = 0;
//     while (type_in_list(list, RDIR))
//     {

//         i++;
//         ;
//     }
// }

char *get_args(t_token_list *list)
{
    char *args;
    char *str;
    char *temp;
    t_token *current;

    if (!list->first->next)
        return (NULL);
    args = NULL;
    current = list->first->next;
    while (current)
    {
        str = ft_strdup(current->token);
        temp = args;
        args = ft_strjoin(args, str);
        if (temp)
            free(temp);
    }
    return (args);
}

// t_command *parse_command(t_token_list *list)
// {
//     t_rdir  **rdirs;
//     int i;
//     t_command *command;

//     // rdirs = malloc(sizeof(t_rdir *));
//     // i = 0;
//     // while (type_in_list(list, RDIR))
//     // {
//     //     i++;
//     //     get_redirections(list, rdirs, i);
//     // }
//     command = malloc(sizeof(t_command));
//     command->cmnd = list->first->token;
//     command->args = get_args(list);
//     if (i > 0)
//         command->rdirs = rdirs;
//     else
//         command->rdirs = NULL;
//     return (command);
// }

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