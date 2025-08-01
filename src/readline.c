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
	if (!line_read)
		return (NULL);
	return (line_read);
}

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
     getchar(); // Get new line character
}

int main()
{
	char *cl_input;
	t_token_list *token_list;
	// t_command *command;
	t_ast *root;

	signal(SIGINT, INThandler);
	while (1)
	{
		cl_input = rl_gets();
		// cl_input = readline("> ");
		if (!cl_input)
		{
			//printf("exit\n");
			break ;
		}
		// if (*cl_input)
			// add_history(cl_input);
		token_list = tokenizer(cl_input); //leaking - due to modifying list in get_rdirs?
		// root = build_ast(token_list);
		root = parser(token_list);
		print_ast(root);
		exec_ast(root);
		free_ast(root);
		// command = parse_command(token_list);
		// print_command(command);
		// free_command(command);
		// print_token_list(token_list); // tokenizer works
		free_token_list(token_list);
		// free(cl_input);
		// root = parser(token_list);
		// print_ast(root);
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