// add header

#include "minishell.h"

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

//     // I need to iterate from behind until I find rdir
//     // I will check the exact rdir type
//     // parse specified tokens to rdir (extract the file based on type)
//     // should I check if the file can be opened?
// }

t_rdir *create_rdir(t_token *rdir_token)
{
    t_rdir *rdir;

    rdir = malloc(sizeof(t_rdir));
    if (!rdir)
        return (NULL);
    rdir->type = get_rdir_type(rdir_token); //will it work if get_rdir_type returns int?
    if (ft_isdigit(rdir_token->token[0]))
        rdir->fd = rdir_token->token[0] - '0'; // check conversion
    else if (rdir->type == IN)
        rdir->fd = STDIN_FILENO;
    else
        rdir->fd = STDOUT_FILENO;
    rdir->target = ft_strdup(rdir_token->next->token);
	rdir->next = NULL;
    rdir->previous = NULL;
    return (rdir);
}

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

void	add_rdir(t_rdir_list **head, t_rdir *rdir)
{
	if (!rdir)
		return ;
	if (!*head)
	{
        *head = malloc(sizeof(t_rdir_list));
        if (!*head)
            return ;
        rdir->next = NULL;
		(*head)->first = rdir;
		(*head)->last = rdir;
		return ;
	}
    rdir->previous = NULL;
    rdir->next = (*head)->first;
    (*head)->first->previous = rdir;
	(*head)->first = rdir;
}

t_rdir_list *get_rdirs(t_token_list *list)
{
	t_rdir_list *rdir_list;
	t_token *current;
	t_rdir *rdir;

	rdir_list = NULL;
	current = list->first;
	while (current)
	{
		if (current->type == RDIR && current->next)
		{
			rdir = create_rdir(current);
			if (!rdir)
				return (free_rdirs(rdir_list), NULL);
			add_rdir(&rdir_list, rdir);
		}
		current = current->next;
	}
	return rdir_list;
}

// test of creating rdir
		// current = token_list->last;
		// while (current)
		// {
		//     if (current->type == RDIR)
		//         create_rdir(current);
		//     current = current->previous;
		// }


void    free_rdirs(t_rdir_list *rdirs)
{
    t_rdir *current;
	t_rdir *temp;

    if (!rdirs)
        return ;
    current = rdirs->first;
    while (current)
    {
        temp = current;
		current = current->next;
		free(temp->target);
		free(temp);
    }
    free(rdirs);
}

// t_rdir_list *get_rdirs(t_token_list *list)
// {
// 	t_rdir_list *rdir_list;
// 	t_token *current;

// 	rdir_list = NULL;
// 	current = list->last;
//     while (current)
//     {
// 		if (current->type == RDIR)
// 		{	
// 			add_rdir(&rdir_list, create_rdir(current));
// 			if (current->next == list->last)
// 			{
//                 current->previous->next = NULL;
// 				list->last = current->previous;
// 			}
// 			else // join two separate ends of linked list
// 			{
// 				current->next->next->previous = current->previous;
// 				current->previous->next = current->next->next;
// 			}
//             current = current->previous;
// 		}
//         else
// 		    current = current->previous;
//     }
// 	return (rdir_list);
// }

