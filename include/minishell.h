/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mika <mika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:37 by dszafran          #+#    #+#             */
/*   Updated: 2025/07/04 07:15:23 by mika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// #define List_count(A) ((A)->count)
// #define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
// #define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)
// #define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL; \
// for(V = _node = L->S; _node != NULL; V= _node = _node->M)

typedef enum {SEP, CMND, QUOT, RDIR, PIPE} t_type; // change types? (add file?) VAR, FILE, STATUS

typedef struct s_token {
	struct s_token *previous;
	char *token;
	t_type type; //should I analize the type during parsing?
	struct s_token *next;
} t_token;

typedef struct s_token_list {
	size_t size; // change to int?
	t_token *first;
	t_token *last;
} t_token_list;


t_token *create_token(char *str, t_type type);
t_token_list *list_init();
void add_back(t_token_list *list, t_token *token);
void add_front(t_token_list *list, t_token *token);
void free_delete_first(t_token_list *list);
void list_del_free(t_token_list *list);
void print_node(t_token *token);
void print_list(t_token_list *list);
char	*ft_strndup(const char *s, int len);
t_type detect_type(char c);
void print_type(int n);
int get_token_len(char *cl_input, t_type type);
void tokenizer(char *cl_input, t_token_list *token_list);
void get_tokens(char *cl_input, t_token_list *token_list);

//do I need easy access to previous token also?

#endif