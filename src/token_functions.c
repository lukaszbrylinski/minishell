// add header

#include "minishell.h"

t_token_list *list_init()
{
    t_token_list *list;

    list = malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return (list);
}

t_token *create_token(char *str, t_type type)
{
	t_token *token;

	if (!str)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (free(str), NULL);
	token->token = str;
	token->type = type;
	token->previous = NULL;
	token->next = NULL;
	return token;
}

void add_back(t_token_list *list, t_token *token)
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
}

void free_token(t_token *token)
{
    if (!token)
        return ;
    if (token->token)
        free(token->token);
    free(token);
}

void free_delete_first(t_token_list *list) //niepotrzebna??
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
    list->size--;
}

void print_token(t_token *token)
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

//     printf("Nodes:\n");
//     print_node(token1); // why only cat is not printed correctly?
//     print_node(token2);
//     print_node(token3);
//     printf("List: \n");
//     print_token_list(list);

//     add_back(list, token1);
//     add_back(list, token2);
//     add_back(list, token3);
//     printf("\n\nList after adding token1, token2, token3:\n");
//     print_token_list(list);

//     printf("\n\nList after deleting first:\n");
//     free_delete_first(list);
//     print_token_list(list);

//     printf("\n\nList after deleating and freeing:\n");
//     list_del_free(list);
//     list = NULL;
//     print_token_list(list);

// }
