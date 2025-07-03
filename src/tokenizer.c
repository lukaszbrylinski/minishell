// add header

// enum for state?

#include "minishell.h"

t_type detect_type(char c)
{
	t_type type;

	if (ft_strchr(" \t\n\v\r\f", c))
		type = SEP;
	else if (ft_strchr("<>", c))
		type = RDIR;
	else if (c == '|')
		type = PIPE;
	else if (ft_strchr("\"\'", c))
		type = QUOT;
	else
		type = CMND;
	return (type);
}

void print_type(int n)
{
	if (n == 0)
		printf("SEP\n");
	if (n == 1)
		printf("CMND\n");
	if (n == 2)
		printf("QUOT\n");
	if (n == 3)
		printf("RDIR\n");
	if (n == 4)
		printf("PIPE\n");
}
// type functions
int iterate(char *cl_input, t_type type)
{
	int i;

	i = 0;
	while (type == detect_type(cl_input[i]))
		i++;
	return (i);
}

// I will treat unclosed quotation as  or.. I can add enum with opening and closed state
int quotation(char *cl_input)
{
	int i;
	char c;

	c = cl_input[0];
	i = 0;
	while (cl_input[++i])
		if (cl_input[i] == c)
			return (i + 2);
	return (i);
}


//while (type == detect_type)
// i++;

void get_tokens(char *cl_input, t_token_list *token_list) //make separate functions for token types
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
		{	
			type = RDIR;
			if (ft_strchr("<>", cl_input[i + 1]))
				j++;
		}
		else if (cl_input[i] == '|')
			type = PIPE;
		else
		{	
			while(!ft_strchr(" \t\n\v\r\f<>|", cl_input[j + 1]))
				j++;
			type = CMND;
		}
		// but I need to also check for WORD - more tricky due to missing " / '
		// for sure I need separate functions for types, maybe I should use enum
		token = create_token(ft_strndup(&cl_input[i], j-i + 1), type);
		add_back(token_list, token);
		i = j;
	}
}

// int main()
// {
// 	char *cl_input;
// 	t_token_list *token_list;

// 	while (1)
// 	{
// 		token_list = list_init();
// 		cl_input = rl_gets();
// 		get_tokens(cl_input, token_list);
// 		print_list(token_list); 
// 		//here should go the parsing and command executing part
// 	}
// 	return (0);	
// }

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