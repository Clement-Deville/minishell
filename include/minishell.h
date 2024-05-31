/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/31 17:16:53 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

// BUILT-IN COMMANDS

int			do_echo(char **args);
int			do_pwd(void);
int			do_env(t_dblist *env);
int			do_export(char **arguments, t_dblist *env);
void		do_exit(char **args);

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
t_bool		patern_match(char *argument, char *d_name);

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

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_MALLOC_FAIL,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

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
	char				*value;
	int					here_doc;
	struct s_red_node	*prev;
	struct s_red_node	*next;
}	t_red_node;

typedef struct s_subs_node
{
	char				*args;
	struct s_subs_node	*prev;
	struct s_subs_node	*next;
}	t_subs_node;

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_wildcard
{
	char				**files;
	struct s_wildcard	*next;
}	t_wildcard;

typedef struct s_compute_cmd
{
	int					ac;
	char				**av;
	char				**expand;
	struct s_wildcard	*wildcard;
	struct s_dlist		*redir;
}	t_compute_cmd;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_node
{
	t_node_type				type;
	t_red_node				*red_node;
	t_subs_node				*sub_node;
	struct s_node			*sub;
	char					*cmd;
	struct s_compute_cmd	*c_cmd;
	struct s_token			*left;
	struct s_token			*rigth;
	struct s_node			*next;
	struct s_node			*prev;
}	t_node;

typedef struct s_mini_env
{
	char		*line;
	char		**env;
	int			in_sub;
	int			exit;
	int			stdin;
	int			stdout;
	t_dblist	*envlst;
	t_token		*tokens;
	t_node		*nodes;
}	t_mini_env;

t_mini_env	*get_ms(void);
void		ft_tokenization(t_mini_env *ms);
void		ft_init_env(char **env);
void		lst_token_add_back(t_token **token_list, t_token *new);

//tokens_helper.c
t_token		*create_new_token(char *value, t_token_type type);
int			ft_is_char(char *str);
int			is_space(char c);

//parser.c
t_node		*ft_parser(t_mini_env *ms, int min_prec);
void		init_parsing(t_mini_env *ms);

//comupte_cmds.c
void		ft_compute_cmds(t_node *node);
char		*ft_str_find_env(char *arg);
int			check_quotes(char *str);

//wildcard.c
int			ft_contains_asterisk(char *str);

//init_here_doc.c
void		ft_init_heredoc(t_node *node);

//clean_ms.c
void		ft_clean_ms(void);

//exec_builtin.c
int			ft_is_builtin(char *arg);

//exec.c
void		start_exec(t_node *node, t_mini_env *ms);
int			exec_node(t_node *node, t_mini_env *ms, t_bool piped, int i);
int			ft_get_exit_status(int status);
int			exec_simple_cmd(t_node *node, t_mini_env *ms, t_bool piped);

//exec_red.c
int			do_out(t_red_node *node, int *status);
int			do_in(t_red_node *node, int *status);
int			do_append(t_red_node *node, int *status);

//exec_builtin.c
int			ft_is_builtin(char *arg);
int			ft_exec_builtin(char **args, t_mini_env *ms);

//error_msg.c
int			ft_err_msg(t_err err);

void		ft_big_free(char **str);

t_path		ft_get_path(char *cmd);

//exec_pipeline.c
int			ft_exec_pipeline(t_node *node, t_mini_env *ms, int i);

int			main_subshell(int ac, char **av, char **env);

void		*ft_garbage(void *str, t_bool clean);

char		*convert(t_node_type type);

void		ft_clear_token(t_token *token);

void 		free_node(t_node *node);

void		ft_clear_envlst(t_mini_env *mini_s);
void		ft_clear_parsing(t_node *nodes);
void		ft_clean_nodes(t_node *node);

#endif
