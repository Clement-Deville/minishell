/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/17 19:13:16 by cdeville         ###   ########.fr       */
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
char		*do_expand(char *arg);

// UTILS

void		print_env(void *content);

typedef enum s_token_type
{
	TOKEN_ELSE,
	TOKEN_RED_IN,
	TOKEN_RED_OUT,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_VAR_ENV,
	TOKEN_HERE_DOC,
	TOKEN_APPEND,
	TOKEN_SUBSHELL_OPEN,
	TOKEN_SUBSHELL_CLOSE,
	TOKEN_NULL,
}	t_token_type;

typedef enum s_red_type
{
	NODE_RED_IN,
	NODE_RED_OUT,
	NODE_APPEND,
	NODE_HERE_DOC,
}	t_red_type;

typedef enum s_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_OR,
	NODE_AND,
}	t_node_type;

typedef struct s_red_node
{
	t_red_type			type;
	// char				*args;
	char				*value;
	struct s_red_node	*prev;
	struct s_red_node	*next;
}	t_red_node;

typedef struct s_node
{
	t_node_type		type;
	t_red_node		*red_node;
	char			*args;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_mini_env
{
	char	*line;
	char	**env;
	t_token	*tokens;
	t_node	*ast;
}	t_mini_env;

void		ft_tokenization(t_mini_env *ms);
void		ft_init_env(char **env, t_mini_env *ms, char *line);
void		lst_token_add_back(t_token **token_list, t_token *new);

//tokens_helper.c
t_token		*create_new_token(char *value, t_token_type type);
int			ft_is_char(char *str);
int			is_space(char c);

//parser.c
t_node	*ft_parser(t_mini_env *ms, int *i, t_token *curr_token);

#endif
