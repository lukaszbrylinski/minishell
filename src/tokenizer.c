// add header

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

// void print_type(int n)
// {
// 	if (n == 0)
// 		printf("SEP\n");
// 	if (n == 1)
// 		printf("CMND\n");
// 	if (n == 2)
// 		printf("QUOT\n");
// 	if (n == 3)
// 		printf("RDIR\n");
// 	if (n == 4)
// 		printf("PIPE\n");
// }

// I will treat unclosed quotation as  or.. I can add enum with opening and closed state
int get_token_len(char *cl_input, t_type type)
{
	int i;
	int c;

	i = 0;
	if (type == QUOT)
	{
		c = cl_input[0];
		while (cl_input[++i])
			if (cl_input[i] == c)
				return (i + 2);
	}
	else if (type == PIPE)
		return (1);
	else
		while (type == detect_type(cl_input[i]))
			i++;
	return (i);
}

t_token_list *tokenizer(char *cl_input)
{
	int i = -1;
	int len;
	t_type type;
	t_token *token;
	t_token_list *token_list;

	token_list = list_init();
	if (!token_list)
		return (NULL);
	while (cl_input[++i])
	{
		type = detect_type(cl_input[i]);
		len = get_token_len(&cl_input[i], type);
		if (type != SEP)
		{
			token = create_token(ft_strndup(&cl_input[i], len), type);
			if (!token)
				return (free_token_list(token_list), NULL);
			add_back(token_list, token);
		}
		i += len - 1;
	}
	return (token_list);
}

void print_token_list(t_token_list *list)
{
    t_token *current;
    if (!list) //|| !list->first
    {
        printf("No list to print\n");
        return ;
    }
    printf("Printing list\n");
    current = list->first;
    while (current)
    {
        print_token(current);
        current = current->next;
    }
}

void free_token_list(t_token_list *list) //przepisać na użycie free token
{
    t_token *current;
    if (!list)
        return ;
    if (!list->first)
        return (free(list));
    current = list->first;
    while (current != NULL)
    {
        current = current->next;
        free_delete_first(list);
    }
    free(list);
}



