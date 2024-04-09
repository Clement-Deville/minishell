/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 11:08:10 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>

typedef struct s_env
{
	char	*value;
	t_bool	export;
}	t_env;

// BUILT-IN COMMANDS

int			do_echo(char *str, t_bool nonewline);
int			do_pwd(void);
int			do_env(t_dblist *env);

// ENV

t_dblist	*generate_env(char **envp);

// UTILS

void		print_env(void *content);

typedef enum  s_token_type
{
    TOKEN_ELSE,
    TOKEN_RED_IN, // --> '<'
    TOKEN_RED_OUT, // --> '>'
    TOKEN_PIPE, // --> '|'
    TOKEN_AND, // --> '&&'
    TOKEN_OR, // --> '||'
    TOKEN_VAR_ENV, // --> '$'
    TOKEN_DELIM_L, // --> '<<'
    TOKEN_DELIM_G, // --> '>>'
    TOKEN_SUBSHELL_OPEN, // --> '('
    TOKEN_SUBSHELL_CLOSE, // --> ')'

} t_token_type;


typedef struct  s_token
{
    t_token_type    type;
    char            *value;
    char            *prev;
    char            *next;
}   t_token;

typedef struct  s_mini_env
{
    char    *line;
    char    **env;
    t_token *tokens;
}   t_mini_env;


void ft_tokenization(t_mini_env *ms);
void    ft_init_env(char **env, t_mini_env *ms, char *line);
void    lst_token_add_back(t_token **token_list, t_token *new);

#endif
