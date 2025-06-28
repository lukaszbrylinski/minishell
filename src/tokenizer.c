// add header

#include "minishell.h"

t_token *create_token(char *str, t_token *previous, t_type type) // do I need a function to create tokens with set next?
{
	t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
	token->token = ft_strdup(str);
	token->type = type;
    token->previous = previous;
	token->next = NULL;
	return (token);
}

t_list *list_init()
{
    t_token_list *list;

    list = malloc(sizeof(list));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return (list);
}

size_t add_back(t_token_list *list, t_token *token) //or keep it void?
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
        token->next = NULL; //should it be start?
        list->last = token;
    }
    list->size++;
    return(list->size);
}

size_t add_front(t_token_list *list, t_token *token)
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
        token->previous = NULL; //should it be last?
        list->first = token;
    }
    list->size++;
    return(list->size);
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

}

// do I need a function to remove specific token? maybe...

size_t remove_front(t_token_list *list, t_token *token) // do I need a function to delete single token?
{
    // should I match token based on address? there can be multiple wih the same containts
    
}

size_t remove_back(t_token_list *list, t_token *token)
{

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