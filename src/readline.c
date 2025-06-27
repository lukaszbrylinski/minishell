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

t_token *create_token(char *str, t_type type)
{
	t_token token;

	token.token = str;
	token.type = type;
	token.next = NULL;
	return (&token);
}

// int	ft_iswspace(int c)
// {
// 	if ((c > 8 && c < 14) || c == ' ')
// 		return (1);
// 	return (0);
// }

char	*ft_strndup(const char *s, int len)
{
	char	*ptr;
	int		i;

	if (!s)
		return (NULL);
	ptr = (char *) malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr[i] = 0, ptr);
}

t_token *tokenizer(char *cl_input) //test it!
{
	int	i;
	int j;
	t_type type;
	t_token *token = NULL;

	i = -1;
	while (cl_input[++i])
	{
		j = i;
		if (ft_strchr(" \t\n\v\r\f", cl_input[i]))
			continue ;
		else if (ft_strchr("<>", cl_input[i]))
			type = RDIR;
			if (ft_strchr("<>", cl_input[i + 1]))
				j++;
		else if (cl_input[i] == '|')
			type = PIPE;
		else
		{	
			while(!ft_strchr(" \t\n\v\r\f<>|", cl_input[j + 1]))
				j++;
			type = WORD;
		}
		token = create_token(ft_strndup(cl_input[i], j), type);
	}
	return (token);
} // create separate functions for iterating through specific token type and incrementing *j
// int execute_prompt(char *prompt)
// {
// 	if (prompt = pwd)
// 	// i need to parse prompt in order to know which part is a command, which is flag and what are the arguments?  
// }

int main()
{
	// t_token *token;

	// token = create_token("hello", RDIR);
	// printf("token: %s, type: %d, next: %p", token.token, token.type, token.next);
	// char *cl_input;

	// while (1)
	// {
	// 	cl_input = rl_gets();
	// 	//here should go the parsing and command executing part
	// }
	return (0);	
}