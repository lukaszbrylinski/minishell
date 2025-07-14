// #include <stdio.h>
// #include <stdlib.h>
// #include <curses.h>
// #include <term.h>
// #include <readline/readline.h>
// #include <readline/history.h>

#include "minishell.h"

static char *line_read = NULL;

// passing emptyline should add it and give the prompt back
// autocompletion of commands after tab? 
char *rl_gets()
{
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("> ");
	if (line_read && *line_read)
		add_history(line_read); // I need additional check for white characters, to make them not save into history
	return (line_read);
}


int main()
{
	char *cl_input;
	t_token_list *token_list;
	// t_token_list *right_child;
	// t_token *current;
	t_rdir *rdir_list;


	while (1)
	{
		token_list = list_init(); // move to tokenizer
		cl_input = rl_gets();
		tokenizer(cl_input, token_list);
		//here should go the parsing and command executing part
		// test of creating rdir_list
		rdir_list = get_rdirs(token_list);
		
		while (rdir_list)
		{
			print_rdir(rdir_list);
			rdir_list = rdir_list->next;
		}
		print_list(token_list);
	}
	return (0);	
}
// du -sh * 2>/dev/null | sort -hr | head -n 10

// int	ft_iswspace(int c)
// {
// 	if ((c > 8 && c < 14) || c == ' ')
// 		return (1);
// 	return (0);
// }


// int execute_prompt(char *prompt)
// {
// 	if (prompt = pwd)
// 	// i need to parse prompt in order to know which part is a command, which is flag and what are the arguments?  
// }

// int main()
// {
// 	char *cl_input;
// 	t_token_list *token_list;
// 	int i;

// 	while (1)
// 	{
// 		token_list = list_init();
// 		cl_input = rl_gets();
// 		i = -1;
// 		while (cl_input[++i])
// 		{	printf("character: %c type: ", cl_input[i]);
// 			print_type(detect_type(cl_input[i]));}
// 			// printf("\n\n");
// 		//here should go the parsing and command executing part
// 	}
// 	return (0);	
// }