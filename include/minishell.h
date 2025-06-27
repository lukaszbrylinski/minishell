/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:37 by dszafran          #+#    #+#             */
/*   Updated: 2025/06/26 15:47:07 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef enum {CMND, WORD, RDIR, PIPE} t_type;

typedef struct s_token {
	char *token;
	t_type type;
	void *next; 
} t_token;
//do I need easy access to previous token also?

#endif