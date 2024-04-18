/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/18 11:00:31 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
#include <stdlib.h>
# include <dirent.h>
# include <signal.h>

typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

// BUILT-IN COMMANDS

int			do_echo(char *str, t_bool nonewline);
int			do_pwd(void);
int			do_env(t_dblist *env);
int			do_export(char **arguments, t_dblist *env);
int			do_exit(char *argument);

// EXPORT

int			export_one(char *argument, t_dblist *env);

// PRINT_EXPORT

void		print_export(t_dblist *env);

// ENV

t_dblist	*generate_env(char **envp);

// VARIABLES

char		*get_name(char *argument);
t_variable	*create_variable(char *argument);
void		destroy_variable(void *content);

// ASTERISK

int			do_asterisk(char *argument);

// CD

int			do_cd(char *directory, t_dblist	*env);

// DIR

int			do_closedir(DIR *dir);
DIR			*do_opendir(void);

// SIGNALS

int			setup_signals(void);

// UNSET

int			do_unset(char **arguments, t_dblist *env);

// UTILS

t_bool		no_value(char *argument);
t_bool		name_exists(char *argument, t_dblist *env);
void		print_variable(void *content);
void		print_variable_export(void *content);

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
	char				*args;
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
t_node		*ft_parser(t_mini_env *ms, int *i, t_token *curr_token);

#endif
