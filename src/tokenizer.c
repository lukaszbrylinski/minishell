// add header

// enum for state?

#include "minishell.h"

void get_tokens(char *cl_input, t_token_list *token_list)
{
	int i;
	int j;
	t_type type;
	t_token *token;

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
		token = create_token(ft_strndup(&cl_input[i], j), type);
		add_back(token_list, token);
	}
}

// t_token *tokenizer(char *cl_input) //test it!
// {
// 	int	i;
// 	int j;
// 	t_type type;
// 	t_token *token = NULL;

// 	i = -1;
// 	while (cl_input[++i])
// 	{
// 		j = i;
// 		if (ft_strchr(" \t\n\v\r\f", cl_input[i]))
// 			continue ;
// 		else if (ft_strchr("<>", cl_input[i]))
// 			type = RDIR;
// 			if (ft_strchr("<>", cl_input[i + 1]))
// 				j++;
// 		else if (cl_input[i] == '|')
// 			type = PIPE;
// 		else
// 		{	
// 			while(!ft_strchr(" \t\n\v\r\f<>|", cl_input[j + 1]))
// 				j++;
// 			type = WORD;
// 		}
// 		token = create_token(ft_strndup(cl_input[i], j), type);
// 	}
// 	return (token);
// } // create separate functions for iterating through specific token type and incrementing *j