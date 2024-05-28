/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/28 15:30:42 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define CANT_EXEC 126
# define DONOT_EXIST 127

typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

// BUILT-IN COMMANDS

int			do_echo(char **args);
int			do_pwd(void);
int			do_env(t_dblist *env);
int			do_export(char **arguments, t_dblist **env);
int			do_exit(char *argument);

// EXPORT

int			export_one(char *argument, t_dblist **env);

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

int			do_cd(char *directory, t_dblist	**env);

// DIR

int			do_closedir(DIR *dir);
DIR			*do_opendir(void);

// SIGNALS

int			setup_signals(void);

// UNSET

int			do_unset(char **arguments, t_dblist **env);

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
	ENO_EXEC_255 = 255,
	ENO_CRITICAL = 300,
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
	char				*args;
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
	int						status;
	int						pid;
	t_node_type				type;
	t_red_node				*red_node;
	t_subs_node				*sub_node;
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
	int			exit;
	int			stdin;
	int			stdout;
	t_dblist	*envlst;
	t_token		*tokens;
	t_node		*nodes;
}	t_mini_env;

// exec_pipeline

int			exec_pipeline(t_node **node, t_dblist **env);
int		exec_single(t_node **node, t_dblist **env);
t_bool	is_pipe_cmd(t_node *node);

typedef struct s_command
{
	int		type;
	char	*sub_node;
	char	**args;
	int		status;
	int		pid;
}	t_command;

t_mini_env	*get_ms(void);
void		ft_tokenization(t_mini_env *ms);
void		ft_init_env(char **env);
void		lst_token_add_back(t_token **token_list, t_token *new);

//tokens_helper.c
t_token		*create_new_token(char *value, t_token_type type);
int			ft_is_char(char *str);
int			is_space(char c);

//parser.c
t_node		*ft_parser(t_mini_env *ms);
t_node		*init_parsing(t_mini_env *ms);

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
int			start_exec(t_node *node, t_dblist **env);

int			ft_get_exit_status(int status);
int			exec_simple_cmd(t_node *node, t_mini_env *ms, t_bool piped);

//exec_red.c
int			do_out(t_red_node *node, int *status);
int			do_in(t_red_node *node, int *status);
int			do_append(t_red_node *node, int *status);

//error_msg.c
int			ft_err_msg(t_err err);

void		ft_big_free(char **str);

t_path		ft_get_path(char *cmd);

int			main_subshell(int ac, char *av, char **env);

// access.c

int			check_for_path_access(char **cmd, t_dblist *env);

// path.c

char		*get_path(t_dblist *env);
char		**parse_path(t_dblist *env);
int			change_path(char **cmd, char *new_path);
char		**add_dir(char **split_path);
char		**add_cmd_to_path(char **split_path, const char *cmd);

char		**list_to_tab(t_dblist *env);

// redirection.c

int			set_input(char *filename, t_node *node);
int			set_output(char *filename, t_node *node);
int			set_input_here_doc(int fd);
int			set_output_append(char *filename, t_node *node);
int			do_redirections(t_node *node);

//	do.c

int			do_dup2(int oldfd, int newfd);
int			do_close(int fd);
int			do_pipe(int pipfd[2]);

# define NO_FORK -2
# define WRITE 1
# define READ 0
# define COMMAND 0
# define SUBSHELL 1
# define FLAG_END 5

#endif
