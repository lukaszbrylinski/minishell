/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:37 by dszafran          #+#    #+#             */
/*   Updated: 2025/07/22 18:28:37 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

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

typedef enum {IN, OUT, AEND, HDOC} t_rdir_type; // AEND_ERR, OUT_ERR

typedef struct s_rdir {
	int fd;
	char *target;
	t_rdir_type	type; //RDIR_IN, RDIR_OUT, RDIR_APPEND etc.
	struct s_rdir *previous;
	struct s_rdir *next;  // pointer to next redirection
} t_rdir;

typedef struct s_rdir_list {
	t_rdir *first;
	t_rdir *last;
} t_rdir_list;

typedef struct s_command {
	char *cmnd;
	char **args;
	t_rdir_list *rdir_list;
} t_command;

typedef struct s_ast {
	enum {CMND_NODE, PIPE_NODE} type;
	union {
		t_command *cmnd;
		struct {
			struct s_ast *left;
			struct s_ast *right;
		} pipe;
	};
} t_ast;


// do I need a structure to store root?

// structure of ast: enum with command and pipe nodes, structure {command, left, right pipe}
// splitting linked list by pipe going from the last token


t_token *create_token(char *str, t_type type);
t_token_list *list_init();
void add_back(t_token_list *list, t_token *token);
void add_front(t_token_list *list, t_token *token);
void free_token(t_token *token);
void free_delete_first(t_token_list *list);
void list_del_free(t_token_list *list);
void print_node(t_token *token);
void print_list(t_token_list *list);
char	*ft_strndup(const char *s, int len);
void    print_ast(t_ast *ast);
t_token *new_create_token(char *str, t_type type);

//TOKENIZER
t_type detect_type(char c);
void print_type(int n);
int get_token_len(char *cl_input, t_type type);
void tokenizer(char *cl_input, t_token_list *token_list);
t_token_list *new_tokenizer(char *cl_input);

//REDIRECTIONS PARSING
int get_rdir_type(t_token *token);
void print_rdir(t_rdir *rdir);
t_rdir *create_rdir(t_token *rdir_token);
void    free_rdirs(t_rdir_list *rdirs);
void	add_rdir(t_rdir_list **head, t_rdir *rdir);
t_rdir_list *get_rdirs(t_token_list *list);

//COMMAND PARSING
char    **append_array(char **array, char *str);
char **get_args(t_token_list *list);
void    print_command(t_command *command);
t_command *parse_command(t_token_list *list);
void free_command(t_command *cmd);

//PARSER
t_token_list *move_tokens(t_token *token);
t_token_list *split_list(t_token_list *list);
int	type_in_list(t_token_list *list, t_type type);
t_ast *create_cmnd_node(t_token_list *list);
t_ast *create_pipe_node(t_token_list *list);
void	print_pipe_node(t_ast *node);
t_ast *parser(t_token_list *list);

//BUILD AST
// t_ast	*create_cmd_node(t_command *cmd);
// t_ast	*create_pipe_node(t_ast *left, t_ast *right);
t_token_list *wrap_sublist(t_token *start, t_token *end, t_token_list *list);
t_ast *parse_tokens(t_token *start, t_token *end, t_token_list *list);
t_ast *build_ast(t_token_list *tokens);
void    print_ast(t_ast *ast);
void free_ast(t_ast *node);
//do I need easy access to previous token also?

//AST TREE


#endif