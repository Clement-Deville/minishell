/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/25 11:50:09 by cdeville         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

# define CANT_EXEC 126
# define DONOT_EXIST 127

typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

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

typedef enum e_err_parse
{
	E_MEMORY = 1,
	E_SYNTAX,
	E_QUOTES,
	E_DQUOTES
}	t_err_parse;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255,
	ENO_CRITICAL = 300,
}	t_err_no;

typedef struct s_parser_error
{
	t_err_parse	type;
	char		*str;
}	t_parser_error;

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
	int						status;
	int						pid;
	t_node_type				type;
	t_red_node				*red_node;
	struct s_node			*sub;
	char					*cmd;
	struct s_compute_cmd	*c_cmd;
	struct s_token			*left;
	struct s_token			*rigth;
	struct s_node			*next;
	struct s_node			*prev;
	t_bool					silent;
}	t_node;

typedef struct s_mini_env
{
	char			*line;
	char			**env;
	char			*balise;
	int				here_doc_quotes;
	int				in_sub;
	int				exit;
	int				stdin;
	int				stdout;
	int				f_or_nf;
	t_parser_error	err;
	t_dblist		*envlst;
	t_token			*tokens;
	t_token			*tmp;
	t_node			*nodes;
	t_bool			signal_int;
	t_bool			signal_quit;
	t_bool			parent;
	t_bool			wait_interrupted;
	int				line_count;
}	t_mini_env;

int			clean_and_exit(int exitno);

// access_utils.c

t_bool		is_path(char *path);
void		print_not_found(char *cmd);
t_bool		is_a_dir(const char *path);

// BUILT-IN COMMANDS

int			do_echo(char **args);
int			do_pwd(t_node *node);
int			do_env(t_node *node, t_dblist *env);
int			do_export(t_node *node, t_dblist **env);
int			do_exit(t_node *node);

// EXPORT

int			export_one(char *argument, t_dblist **env, t_bool silent);

// PRINT_EXPORT

void		print_export(t_dblist *env);

// ENV

t_dblist	*generate_env(char **envp);
char		*catch_value(char *name, t_dblist *env);
t_bool		is_valid_name(char *name);

// VARIABLES

char		*get_name(char *argument);
t_variable	*create_variable(char *argument);
void		destroy_variable(void *content);

// ASTERISK

int			do_asterisk(char *argument);
t_bool		patern_match(char *argument, char *d_name);

// CD

int			do_cd(t_node *node, t_dblist	**env);

// DIR

int			do_closedir(DIR *dir);
DIR			*do_opendir(void);

// SIGNALS

void		check_signals(void);
int			setup_signals(void);
int			set_ignore_signals(void);
int			set_child_signals(void);
int			set_wait_signals(void);

// signal_handlers.c

void		wait_handler(int signo);
void		handle_signal(int signo);
void		handle_signal_child(int signo);

// UNSET

int			do_unset(char **arguments, t_dblist **env);

// UTILS

t_bool		no_value(char *argument);
t_bool		name_exists(char *argument, t_dblist *env);
void		print_variable(void *content);
void		print_variable_export(void *content);
int			nbr_of_args(char **args);

// env_utils.c

void		print_variable(void *content);
void		print_filled_variable(void *content);
t_bool		is_valid_name(char *name);

// exec_pipeline

int			exec_pipeline(t_node **node, t_dblist **env);
int			exec_single(t_node **node, t_dblist **env);
t_bool		is_pipe_cmd(t_node *node);

typedef struct s_command
{
	int		type;
	char	*sub_node;
	char	**args;
	int		status;
	int		pid;
}	t_command;

t_mini_env	*get_ms(void);
int			ft_tokenization(t_mini_env *ms);
void		ft_init_env(char **env);
void		lst_token_add_back(t_token **token_list, t_token *new);
int			ft_add_token_sign(char **line, t_token **t_list,
				t_token_type type, int i);

//token_finder.c
void		ft_token_identify(char **line, t_token **t_list);
int			ft_compare_line_token(char *line);

//tokens_helper.c
t_token		*create_new_token(char *value, t_token_type type);
t_bool		ft_skip_quotes(char *line, size_t *i);
int			ft_is_char(char *str);
int			ft_is_quote(char c);
int			is_space(char c);

//wildcard.c
int			ft_contains_asterisk(char *str);

//init_here_doc.c
int			ft_init_heredoc(t_node *node);

//clean_ms.c
void		ft_clean_ms(void);

//exec_builtin.c
int			ft_is_builtin(char *arg);

//exec.c
int			start_exec(t_node *node, t_dblist **env);

int			ft_get_exit_status(int status);
int			exec_simple_cmd(t_node *node, t_mini_env *ms, t_bool piped);

// exec_here_doc.c

int			ft_heredoc_go_expand(t_node *node);
int			exec_here_doc(t_node *nodes);

// exec_builtin.c

int			exec_builtin(t_node *node, t_dblist **env);

// exec_no_cmd.c

int			fake_set_input(char *filename);
int			fake_set_output(char *filename);
int			fake_set_output_append(char *filename);
int			do_no_cmd(t_node *node);

// exec_sub.c

int			exec_sub(t_node *node, t_dblist **env);

// exec_standard.c

int			exec(char **cmd, char *env[]);
int			do_wait(int pid);
int			clean_and_exit(int exitno);
int			exec_standard(t_node **node, t_dblist **env);

// exec_utils.c

t_bool		is_builtin(t_node *node);
t_bool		is_pipeline(t_node *node);
t_bool		is_not_a_cmd(t_node *node);
t_bool		is_subshell(t_node *node);
t_bool		is_empty(t_node *node);

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

// path_utils.c

int			len(char **split);
char		*get_path(t_dblist *env);

// path.c
char		*get_path(t_dblist *env);
char		**parse_path(t_dblist *env);
int			change_path(char **cmd, char *new_path);
char		**add_dir(char **split_path);
char		**add_cmd_to_path(char **split_path, const char *cmd);
char		**list_to_tab(t_dblist *env);

//parser_init.c
t_node		*ft_parser(t_mini_env *ms, int min_prec);
void		init_parsing(t_mini_env *ms);

//parser.c
t_red_node	*ft_create_red_node(t_token_type type, char *value);
t_node		*ft_simple_cmd(t_mini_env *ms);
t_node		*ft_start(t_mini_env *ms, int min_prec);
t_node		*ft_handle_tokens(t_mini_env *ms, t_node *node, int min_prec);
t_node		*ft_recursive_parse(t_mini_env *ms, t_node *node, int min_prec);

// parser_utils_tokens.c
int			ft_is_redir(t_token_type type);
int			ft_get_node_type(t_token_type type);
t_red_type	ft_get_red_type(t_token_type type);
char		*ft_add_args(t_token_type node);

// parser_check_sub.c
int			ft_check_subs(t_token *token, int min_prec);
int			sub_in_sub_error(t_token *token);

// parser_utils_nodes.c
t_node		*ft_new_node(t_node_type type);
int			ft_join_args(char **args, t_token *token);
void		ft_add_red_node(t_red_node **node, t_red_node *new);
int			ft_get_red_node(t_red_node **node, t_mini_env *ms);
void		ft_add_back_sub(t_subs_node **lst, t_subs_node *new);

// pipe_fd_utils.c

int			connect_read(int *pipefd);
int			connect_write(int *pipefd);
int			close_useless_fd(int *pipefd, int size);
int			close_parent(int *pipefd, int size);
int			allocate(int **pipefd, int nbr_of_cmds);

// pipe_utils.c

void		init(t_node *node);
t_bool		are_in_child(int pid1);
t_bool		is_cmd_executable(t_node *node);
t_bool		is_pipe_cmd(t_node *node);
int			nbr_of_cmds(t_node *node);;
// redirection.c

int			set_input(char *filename, t_node *node);
int			set_output(char *filename, t_node *node);
int			set_input_here_doc(int fd);
int			set_output_append(char *filename, t_node *node);
int			do_redirections(t_node *node);

// variable_utils.c

char		*get_variable(t_variable *variable);
char		**list_to_tab(t_dblist *env);
int			dlst_size(t_dblist *lst);

//	do.c

int			do_dup2(int oldfd, int newfd);
int			do_close(int fd);
int			do_pipe(int pipfd[2]);

// main.c

char		*get_balise(void);

// init_minishell.c

int			init_minishell(void);
t_mini_env	*get_ms(void);

# define NO_FORK -2
# define WRITE 1
# define READ 0
# define COMMAND 0
# define SUBSHELL 1
# define FLAG_END 5

void		*ft_garbage(void *str, t_bool clean);

char		*convert(t_node_type type);

void		ft_clear_token(t_token *token);

void		free_node(t_node *node);

// balise.c

char		*get_balise(void);
char		*set_color(void);
void		clean_balise(void);

//clean_env.c
void		free_variable(void *content);
void		ft_clear_envlst(t_mini_env *mini_s);
void		ft_clean_ms(void);
void		ft_del(void *ptr);

//clear_parsing.c
void		ft_clear_token(t_token *token);
void		ft_free_red_nodes(t_red_node *red_node);
void		ft_free_c_cmd_expand(char **expand);
void		ft_clear_parsing(t_node *nodes);
void		ft_clean_nodes(t_node *node);

//parser_utils_error.c
void		ft_set_parse_err(t_err_parse type);
void		ft_handle_parse_err(t_mini_env *ms);

//compute_wildcards.c
char		**ft_handle_wildcard(char **glob, t_node *node);
char		**ft_expand_wildcard(char *str, t_node *node);
char		**ft_join_wildcard(t_node *node);
int			is_in_quotes(char *str);

//compute_check_quotes.c
int			count_single_quotes(char *str, int *i);
int			count_double_quotes(char *str, int *i);
void		set_error(int count, int count2);
int			check_quotes(char *str);

//comupte_cmds.c
char		*clean_node(char *str);
char		**ft_expand(char *str, t_node *node);
char		*remove_quotes_from_str(char *str);
char		*cut_quotes(char *str);
int			init_cmp(t_node *node);
void		ft_compute_cmds(t_node *node);

//compute_handle_arg.c
char		*ft_handle_arg(char *str, int *i);
char		*ft_handle_dq_arg(char *str, int *i);
char		*ft_handle_dollar(char *str, int *i);
char		*ft_handle_simple_quotes(char *str, int *i);
char		*ft_handle_double_quotes(char *str, int *i);

//compute_pre_expand.c
char		*ft_handle_quotes(char *str, int *i);
char		*ft_expand_loop(char *str, char *tmp, int i);
char		*ft_cmd_pre_expand(char *str);

//compute_alloc.c
void		ft_skip_word(char const *s, size_t	*i);
char		**ft_allocater(char const *s, char **str);

//compute_split_args_utils.c
int			find_quotes(char c);
int			is_quotes(char c, char x);
char		assign_quote(char c);
char		*process_word(char *str, int *i, int *count);
char		**free_split_args(char **tmp, int j);
char		**ft_expander_split(char const *s, t_node *node);

//compute_utils.c
int			init_node(t_node *node);
int			ft_is_valid_arg(char c);
char		*ft_str_find_env(char *arg);
void		ft_big_free(char **str);
void		free_node(t_node *node);

//compute_wildcards_utils.c
char		**no_asterisk(char *str);
int			ft_visible(char *entry);
int			tab_size(char **tab);
void		ft_swap(char **a, char **b);
int			name_cmp(char *file1, char *file2);

//compute_wildcards_thereisasterix.c
void		free_wildcards(t_wildcard *wildcard);
char		**there_asterisk(char *str, int i);
char		**ft_sort_tab(char **argv, int size);

//init_here_doc_utils.c
int			ft_is_delimiter(char *str, char *line);
void		*ft_garbage(void *str, t_bool clean);
int			ft_heredoc_handle_dollar(char *str, int i, int fd);
void		ft_heredoc_expand(char *str, int fd);
int			ft_check_here_quotes(char *str);

//init_here_doc.c
void		ft_heredoc_sigint_handler(int signum);
int			ft_error_exe(int p[2], int pid);
void		ft_exit_mess(t_red_node *node);
int			limiter_quotes_check(t_red_node *node);

//process_here_doc.c
void		ft_heredoc(t_red_node *node, int p[2]);
int			process_here_doc(t_red_node *tmp);

char		*ft_strip_quotes(char *str);
int			init_red_cmp(t_red_node *node);

//exec_here_doc_expand.c
int			ft_heredoc_go_expand(t_node *node);

//exec_here_doc.c
int			open_tmp_file(int *tmp_fd);
int			process_heredoc(t_node *node, int tmp_fd);
int			copy_to_final_heredoc(int tmp_fd);
int			finalize_heredoc(t_node *node);

//exec.c
t_bool		is_subshell(t_node *node);
void		dodge_cmd(t_node **node);
int			ft_heredoc_go_expand(t_node *node);

// readline.c

void		do_readline(void);

#endif
