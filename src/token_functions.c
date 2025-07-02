// add header

#include "minishell.h"

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

t_token *create_token(char *str, t_type type) // do I need a function to create tokens with set next?
{
	t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
	token->token = ft_strdup(str);
	token->type = type;
    token->previous = NULL;
	token->next = NULL;
	return (token);
}

t_token_list *list_init()
{
    t_token_list *list;

    list = malloc(sizeof(list));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return (list);
}

void add_back(t_token_list *list, t_token *token) //or keep it void?
{
    if (!token)
        return ;
    if (list->size == 0)
    {
        list->first = token;
        list->last = token; //should it be NULL?
    }
    else
    {
        token->previous = list->last;
        list->last->next = token;
        token->next = NULL; //should it be start?
        list->last = token;
    }
    list->size++;
    // return(list->size);
}

void add_front(t_token_list *list, t_token *token)
{
    if (!token)
        return ;
    if (list->size == 0)
    {
        list->first = token;
        list->last = token; //should it be NULL?
    }
    else
    {
        token->next = list->first;
        list->first->previous = token;
        token->previous = NULL; //should it be last?
        list->first = token;
    }
    list->size++;
    // return(list->size);
}

void free_delete_first(t_token_list *list)
{
    t_token *temp;

    if (!list || !list->first)
        return ;
    temp = list->first;
    list->size--;
    list->first = list->first->next;
    if (list->first != NULL)
        list->first->previous = NULL;
    free(temp->token);
    free(temp);
}

void list_del_free(t_token_list *list)
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

void print_node(t_token *token)
{
    printf("Token: %s\nType %d\n", token->token, token->type);
    if (token->previous)
        printf("Previous: %s\n", token->previous->token);
    else
        printf("Previous: NULL\n");
    if (token->next)
        printf("Next: %s\n\n", token->next->token);
    else
        printf("Next: NULL\n\n");
}

// void print_list(t_token_list *list)
// {

// }

// do I need a function to remove specific token? maybe...

// size_t remove_front(t_token_list *list, t_token *token) // do I need a function to delete single token?
// {
    // should I match token based on address? there can be multiple wih the same containts
    
// }

// size_t remove_back(t_token_list *list, t_token *token)
// {

// }

// no need - I keep size in structure and update inside functions
// size_t list_len(t_token list)
// {
//     size_t len;

//     if (!list)
//         return (0);
//     len = 0;
//     while(list->first->token != list->last->token)
//     {
//         len++;
//         list->first = list->first->next;
//     }  
// }

// int main()
// {
//     t_token_list *list;
//     t_token *token1;
//     t_token *token2;
//     t_token *token3;

//     list = list_init();
//     printf("initialized list: \nsize: %zu\n\n", list->size); //\nfirst: %s\nlast: %s , list->first->token, list->last->token

//     token1 = create_token("cat", CMND);
//     token2 = create_token(">>", RDIR); //I specify previous inside add functions - no need to keep it here
//     token3 = create_token("text.txt", WORD);

//     // how to print nodes if they are freed/null?
//     // i need to polish my print function to be error prone (or accept segfaults)

//     print_node(token1);
//     print_node(token2);
//     print_node(token3);

//     add_back(list, token1);
//     add_back(list, token2);
//     add_back(list, token3);

//     print_node(token1);
//     print_node(token2);
//     print_node(token3);

// }