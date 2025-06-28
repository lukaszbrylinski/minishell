/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mika <mika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:37 by dszafran          #+#    #+#             */
/*   Updated: 2025/06/28 17:23:43 by mika             ###   ########.fr       */
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

typedef enum {CMND, WORD, RDIR, PIPE} t_type; // change types? (add file?)

typedef struct s_token {
	t_token *previous;
	char *token;
	t_type type; //should I analize the type during parsing?
	t_token *next;
} t_token;

typedef struct s_token_list {
	size_t size; // change to int?
	t_token *first;
	t_token *last;
} t_token_list;

//do I need easy access to previous token also?

#endif