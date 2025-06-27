#include "minishell.h"

t_token *create_token(char *str, t_token *previous, t_type type) // pss next also?
{
	t_token token;

	token.token = str;
	token.type = type;
    token.previous = previous;
	token.next = NULL;
	return (&token);
}

size_t add_back(t_token_list *list, t_token *token) //or keep it void?
{
    if (!token)
        return ;
    if (!list)
    {
        list->size = 1;
        list->first = token;
        list->last = token; //should it be NULL?
    }
    else
    {
        list->size++;
        token->previous = list->last;
        token->next = NULL; //should it be start?
        list->last = token;
    }
    return(list->size)
}

size_t add_front(t_token_list *list, t_token *token)
{
    if (!token)
        return ;
    if (!list)
    {
        list->size = 1;
        list->first = token;
        list->last = token; //should it be NULL?
    }
    else
    {
        list->size++;
        token->next = list->first;
        token->previous = NULL; //should it be last?
        list->first = token;
    }
    return(list->size)
}

size_t delete_token(t_token_list *list, t_token *token)
{
    // should I match token based on address? there can be multiple wih the same containts
    
}

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