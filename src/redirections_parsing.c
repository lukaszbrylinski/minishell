// add header

#include "minishell.h"

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

// else
// handle type = <> (read and write);
int get_rdir_type(t_token *token)
{
    int is_fd;

    if (ft_isdigit(token->token[0]))
        is_fd = 1;
    else
        is_fd = 0;
    if (ft_strlen(token->token) - is_fd == 2)
    {   
        if (token->token[0 + is_fd] == token->token[1 + is_fd])
        {
            if (token->token[0 + is_fd] == '<')
                return (HDOC);
            else
                return (AEND);
        }
    }
    else
    {   
        if (token->token[0 + is_fd] == '<')
            return (IN);
        else
            return (OUT);
    }
    return (-1);
}

// test of getting rdir type
// current = token_list->last;
// while (current)
// {
//     if (current->type == RDIR)
//         printf("RDIR: %s, type: %d\n", current->token, get_rdir_type(current));
//     current = current->previous;
// }

void print_rdir(t_rdir *rdir)
{
    if (!rdir)
    {    
        (printf("No rdir to print"));
        return ;
    }
    printf("Printing rdir:\n");
    printf("fd: %d, target: %s, type: %d\n", rdir->fd, rdir->target, rdir->type);
}

//     // I need to iterate from behind until I find rdir
//     // I will check the exact rdir type
//     // parse specified tokens to rdir (extract the file based on type)
//     // should I check if the file can be opened?
// }

t_rdir *create_rdir(t_token *rdir_token)
{
    t_rdir *rdir;

    rdir = malloc(sizeof(rdir));
    if (!rdir)
        return (NULL);
    rdir->type = get_rdir_type(rdir_token); //will it work if get_rdir_type returns int?
    if (ft_isdigit(rdir_token->token[0]))
        rdir->fd = rdir_token->token[0] - '0'; // check conversion
    else if (rdir->type == IN)
        rdir->fd = STDIN_FILENO;
    else
        rdir->fd = STDOUT_FILENO;
    rdir->target = rdir_token->next->token;
	rdir->next = NULL;
    // testing
    printf("Rdir: %s\n", rdir_token->token);
    print_rdir(rdir);
    return (rdir);
}
// test of creating rdir
		// current = token_list->last;
		// while (current)
		// {
		//     if (current->type == RDIR)
		//         create_rdir(current);
		//     current = current->previous;
		// }

// size_t  getlen_2d(t_rdir **rdirs)
// {
//     size_t  i;

//     i = 0;
//     while(rdirs && rdirs[i])
//         i++;
//     return (i);
// }

void    free_rdirs(t_rdir **rdirs) // TO DO: rewrite
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

// t_rdir **append_2d(t_rdir **rdirs, t_rdir *rdir)
// {
//     t_rdir **joined;
//     int i;

//     if (!rdir && !rdirs)
//         return (NULL);
//     joined = malloc(sizeof(t_rdir *) * (getlen_2d(rdirs) + 2));
// 	if (!joined)
// 		return (NULL);
//     i = -1;
//     while (rdirs && rdirs[++i])
//         joined[i] = rdirs[i];
//     joined[i] = rdir;
//     joined[++i] = NULL;
//     free(rdirs); //check if it won't affect singular rdirs
//     return (joined);
// }

void	add_rdir(t_rdir *head, t_rdir *rdir)
{
	t_rdir *current;
	if (!rdir)
	{	
		head = rdir;
		return ;
	}
	current = head;
	while (current->next)
		current = current->next;
	current = rdir;
	// rdir->next = NULL;
}

// I need to add one more star to modify it (?)
// I need to realloc memory for the list of redirections 
t_rdir *get_rdirs(t_token_list *list)
{
	t_rdir *head;
	t_token *current;
	t_token *temp;

	head = NULL;
    while (current)
    {
		if (current->type == RDIR)
		{	
			add_rdir(head, create_rdir(current));
			// move deleting to the separate function
			temp = current;
			if (current == list->last)
			{
				current->previous->next = NULL;
				list->last = current->previous;
			}
			else // join two separate ends of linked list
			{
				current->next->previous = current->previous;
				current->previous->next = current->next;
			}
			free_token(temp);
		}
		current = current->previous;
    }
	return (head);
}