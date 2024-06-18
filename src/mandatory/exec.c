/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:47:07 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/18 12:13:07 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_builtin(t_node *node)
{
	char	**command;

	if (node->c_cmd == NULL)
		return (FALSE);
	command = node->c_cmd->expand;
	if (ft_strncmp(command[0], "echo", 6) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "export", 8) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "unset", 7) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "exit", 6) == 0)
		return (TRUE);
	return (FALSE);
}

int	exec(char **cmd, char *env[])
{
	// IL FAUT TRANSFORMER LA LIST EN UN TAB POUR L'EXEC
	if (execve(cmd[0], cmd, env) == -1)
	{
		perror("Probleme a l'execution de la commande");
		return (1);
	}
	return (0);
}

int	dlst_size(t_dblist *lst)
{
	t_dblist	*actual;
	int			count;

	if (!lst)
		return (0);
	count = 1;
	actual = lst;
	while (actual->next)
	{
		count++;
		actual = actual->next;
	}
	return (count);
}

char	*get_variable(t_variable *variable)
{
	char	*str;
	char	*temp;

	str = ft_strdup(variable->name);
	if (str == NULL)
		return (NULL);
	temp = str;
	str = ft_strjoin(str, "=");
	if (str == NULL)
		return (perror("Malloc"), free(temp), NULL);
	free(temp);
	temp = str;
	str = ft_strjoin(str, variable->value);
	if (str == NULL)
		return (perror("Malloc"), free(temp), NULL);
	return (free(temp), str);
}

t_bool	is_pipeline(t_node *node)
{
	if (node->rigth && node->rigth->type == TOKEN_PIPE)
		return (TRUE);
	return (FALSE);
}

char	**list_to_tab(t_dblist *env)
{
	char	**tab;
	int		i;
	int		size;

	size = dlst_size((env));
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (tab == NULL)
		return (perror("Malloc"), NULL);
	tab[size] = NULL;
	i = 0;
	while (env)
	{
		tab[i] = get_variable((t_variable*)(env->content));
		if (tab[i] == NULL)
		{
			while (i >= 0)
				free(tab[i--]);
			return (free(tab), NULL);
		}
		env = env->next;
		i++;
	}
	return (tab);
}

int	do_wait(int pid)
{
	int	status;

	//SETOFF
	set_ignore_signals();
	status = 0;
	if (waitpid(pid, &status, 0) == -1)
		return (setup_signals(), perror("Wait error"), ENO_CRITICAL);
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	exec_builtin(t_node *node, t_dblist **env)
{
	// A verfier

	int		pid;
	int		status;
	char	**command;
	int		red_status;


	command = node->c_cmd->expand;
	node->silent = FALSE;
	// gerer les cas qui utilisent l'environnement
	pid = fork();
	if (pid < 0)
		return (perror("Fork error"), ENO_CRITICAL);
	if (pid == 0)
	{
		red_status = do_redirections(node);
		if (red_status == -1)
		{
			ft_clean_ms();
			exit (ENO_CRITICAL);
			// NEED TO EXIT?
		}
		if (red_status)
		{
			ft_clean_ms();
			exit (1);
		}
		if (ft_strncmp(command[0], "echo", 6) == 0)
			if (do_echo(command))
			{
				ft_clean_ms();
				exit (1);
			}
		if (ft_strncmp(command[0], "cd", 3) == 0)
			if (do_cd(node, env))
			{
				ft_clean_ms();
				exit (1);
			}
		if (ft_strncmp(command[0], "export", 8) == 0)
			if (do_export(node, env))
			{
				ft_clean_ms();
				exit (1);
			}
		if (ft_strncmp(command[0], "env", 4) == 0)
			if (do_env(node, *env))
			{
				ft_clean_ms();
				exit (1);
			}
		if (ft_strncmp(command[0], "pwd", 4) == 0)
			if (do_pwd(node))
			{
				ft_clean_ms();
				exit (1);
			}
		if (ft_strncmp(command[0], "unset", 7) == 0)
			if (do_unset(&command[1], env))
			{
				ft_clean_ms();
				exit (1);
			}
		if (ft_strncmp(command[0], "exit", 6) == 0)
			if (do_exit(node))
			{
				ft_clean_ms();
				exit (1);
			}
		// NEED TO FREE EVERYTHING BEFORE EXITING
		ft_clean_ms();
		exit (0);
	}
	status = do_wait(pid);
	node->silent = TRUE;
	if (ft_strncmp(command[0], "export", 8) == 0)
		if (do_export(node, env))
			return (1);
	if (ft_strncmp(command[0], "cd", 3) == 0)
		if (do_cd(node, env))
			return (1);
	if (ft_strncmp(command[0], "unset", 7) == 0)
		if (do_unset(&command[1], env))
			return (1);
	if (ft_strncmp(command[0], "exit", 6) == 0)
		if (do_exit(node))
			return (1);
	return (status);
}

// int	exec_builtin(t_node *node, t_dblist **env)
// {
// 	// A verfier

// 	int		pid;
// 	int		status;
// 	char	**command;


// 	command = node->c_cmd->expand;
// 	// gerer les cas qui utilisent l'environnement
// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("Fork error"), ENO_CRITICAL);
// 	if (pid == 0)
// 	{
// 		if (do_redirections(node))
// 			exit (1);
// 		if (ft_strncmp(command[0], "echo", 6) == 0)
// 			if (do_echo(command))
// 				exit (1);
// 		if (ft_strncmp(command[0], "cd", 3) == 0)
// 			if (do_cd(command[1], env))
// 				exit (1);
// 		if (ft_strncmp(command[0], "export", 8) == 0)
// 			if (do_export(&command[1], env))
// 				exit (1);
// 		if (ft_strncmp(command[0], "env", 4) == 0)
// 			if (do_env(*env))
// 				exit (1);
// 		if (ft_strncmp(command[0], "pwd", 4) == 0)
// 			if (do_pwd())
// 				exit (1);
// 		if (ft_strncmp(command[0], "unset", 7) == 0)
// 			if (do_unset(&command[1], env))
// 				exit (1);
// 		if (ft_strncmp(command[0], "exit", 6) == 0)
// 			if (do_exit(command[1]))
// 				exit (1);
// 		// NEED TO FREE EVERYTHING BEFORE EXITING
// 		exit (0);
// 	}
// 	if (do_wait(pid, &status) == -1)
// 		return (ENO_CRITICAL);
// 	if (ft_strncmp(command[0], "cd", 3) == 0)
// 		if (do_cd(command[1], env))
// 			return (1);
// 	if (ft_strncmp(command[0], "export", 8) == 0)
// 		if (do_export(&command[1], env))
// 			return (1);
// 	if (ft_strncmp(command[0], "unset", 7) == 0)
// 		if (do_unset(&command[1], env))
// 			return (1);
// 	if (ft_strncmp(command[0], "exit", 6) == 0)
// 		if (do_exit(command[1]))
// 			return (1);
// 	return (status);
// }

int	exec_standard(t_node **node, t_dblist **env)
{
	int		access_status;
	int		pid;
	char	**tab_env;
	int		status;
	int		red_status;
	int		tmp; //CODE RAJOUTE (SIM) -> POUR FREE EN SORTANT DES CHILDS)

	pid = fork();
	if (pid < 0)
		return (perror("Fork error"), ENO_CRITICAL);
	if (pid == 0)
	{
		set_child_signals();
		red_status = do_redirections(*node);
		if (red_status == -1)
		{
			ft_clean_ms();
			exit (ENO_CRITICAL);
			// NEED TO EXIT?
		}
		if (red_status)
		{
			ft_clean_ms();
			exit (1);
		}
		access_status = check_for_path_access(&((*node)->c_cmd->expand[0]), *env);
		if (access_status == -1)
		{
			ft_clean_ms();;
			exit (ENO_CRITICAL);
		}
		if (access_status)
		{
			ft_clean_ms();
			exit (access_status);
		}
		// NEED TO FREE EVERYTHING HERE
		tab_env = list_to_tab(*env);
		if (tab_env == NULL)
		{
			ft_clean_ms();
			exit (1);
		}
		tmp = exec((*node)->c_cmd->expand, tab_env);
		ft_clean_ms();
		exit (tmp);
	}
	status = do_wait(pid);
	return (status);
}

int	exec_sub(t_node *node, t_dblist **env)
{
	int	pid;
	int	red_status;
	int	tmp;
	t_node	*subnode;

	subnode = node->sub;
	pid = fork();
	if (pid < 0)
		return (perror("Fork"), ENO_CRITICAL);
	if (pid == 0)
	{
		// fprintf(stderr, "%s\n", subnode->cmd);
		// if (do_redirections(subnode))
		// 	exit (1);
		// if ((node)->next->red_node !=NULL)
        // {
        //     if (do_redirections((node)->next))
        //     {
        //         exit (1);
        //     }
        // }
		red_status = do_redirections(node);
		if (red_status == -1)
		{
			ft_clean_ms();
			return (ENO_CRITICAL);
			// NEED TO EXIT?
		}
		if (red_status)
		{
			ft_clean_ms();
			exit (1);
		}
		get_ms()->parent = FALSE;
		tmp = start_exec(subnode, env);
		ft_clean_ms();
		exit (tmp);
	}
	get_ms()->exit = do_wait(pid);
	if (get_ms()->exit == -1)
		return (ENO_CRITICAL);
	return (get_ms()->exit);
	// Need to leave program properly
}

// int	exec_subshell(t_node **node, t_dblist **env)
// {
// 	int		pid;
// 	char	**tab_env;
// 	int		status;

// 	// GERER la transmission des ENO CRITICAL et la gestion de la memoire pour chaqeu process
// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("Fork error"), ENO_CRITICAL);
// 	if (pid == 0)
// 	{
// 		if (do_redirections(*node))
// 			exit (1);
// 		tab_env = list_to_tab(*env);
// 		if (tab_env == NULL)
// 			exit (1);
// 		exit (main_subshell(ft_strlen((*node)->sub_node->args), (*node)->sub_node->args, tab_env));
// 	}
// 	status = do_wait(pid);
// 	return (status);
// 	(void)node;
// 	(void)env;
// 	return (0);
// }

t_bool	is_subshell(t_node *node)
{
	if ((node)->sub)
		return (TRUE);
	return (FALSE);
}

t_bool	is_not_a_cmd(t_node *node)
{
	if (node->c_cmd->expand == NULL)
		return (TRUE);
	return (FALSE);
}

int	fake_set_input(char *filename)
{
	int	fd;

	if (access(filename, R_OK) != 0)
		return (perror(filename), 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (perror(filename), 1);
		return (perror("Open"), -1);
	}
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (0);
}

int	fake_set_output(char *filename)
{
	int	fd;

	if (access(filename, W_OK) != 0 && errno != ENOENT)
		return (perror(filename), 1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (perror(filename), 1);
		return (perror("Open"), -1);
	}
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (0);
}

int	fake_set_output_append(char *filename)
{
	int	fd;

	if (access(filename, W_OK) != 0 && errno != ENOENT)
		return (perror(filename), 1);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (perror(filename), 1);
		return (perror("Open"), -1);
	}
	if (do_close(fd) == -1)
		return (-1);
	return (0);
}

int do_no_cmd(t_node *node)
{
	t_red_node	*tmp;
	int			status;

	if (node->red_node == NULL)
		return (0);
	status = 0;
	tmp = node->red_node;
	while (tmp)
	{
		if (tmp->type == NODE_RED_IN)
			status = fake_set_input(tmp->value);
		else if (tmp->type == NODE_RED_OUT)
			status = fake_set_output(tmp->value);
		else if (tmp->type == NODE_APPEND)
			status = fake_set_output_append(tmp->value);
		if (status == -1)
			return (ENO_CRITICAL);
		if (status)
			return (status);
		// NEED TO EXIT ?
		tmp = tmp->next;
	}
	return (0);
}

t_bool	is_empty(t_node *node)
{
	if (!node || !node->c_cmd || !node->c_cmd->expand
		|| !node->c_cmd->expand[0] )
		return (TRUE);
	return (FALSE);
}

int	exec_single(t_node **node, t_dblist **env)
{
	if (is_subshell(*node))
		return (exec_sub((*node),  env));
	if (is_empty(*node))
		return (0);
	if (is_not_a_cmd(*node) && !(*node)->sub)
		return (do_no_cmd(*node));
	else if (is_builtin(*node))
		return (exec_builtin((*node), env));
	else
		return (exec_standard(node, env));
}

void	dodge_cmd(t_node **node)
{
	if (is_pipeline(*node))
	{
		while (is_pipe_cmd((*node)))
			(*node) = (*node)->next;
	}
	else
		(*node) = (*node)->next;
}

int	exec_cmd(t_node **node, t_dblist **env)
{
	int	status;

	if (is_pipeline(*node))
		status = exec_pipeline(node, env);
	else
		status = exec_single(node, env);
	return (status);
	// NEED TO CHECK IF CRITICAL ERROR
}

// int	start_exec(t_node *node, t_dblist **env)
// {
// 	int	exit_value;
// 	int	status;

// 	exit_value = 0;
// 	status = 0;
// 	// t_node	*temp;
// 	// temp = node;
// 	// while (temp)
// 	// {
// 	// 	ft_printf("Adr: %p\n", temp);
// 	// 	temp = temp->next;
// 	// }
// 	if (node == NULL)
// 		return (1);
// 	while (node)
// 	{
// 		ft_printf("Node TyPE: %d\n", node->type);
// 		if (node->next)
// 			ft_printf("Node next TyPE: %d\n", node->next->type);
// 		if (node->prev && ((node->prev->type == NODE_AND && status != 0)
// 				|| (node->prev->type == NODE_OR && status == 0)))
// 			dodge_cmd(&node);
// 		else
// 		{
// 			status = exec_cmd(&node, env);
// 			dodge_cmd(&node);
// 		}
// 		// NEED TO CHECK FOR CRITICAL ERROR (WHAT ABOUT SUBSHELLS?)
// 	}
// 	return (status);
// }

int	start_exec(t_node *node, t_dblist **env)
{
	if (node == NULL)
		return (1);
	while (node)
	{
		if (node->red_node != NULL && node->red_node->here_doc != 0)
			ft_heredoc_go_expand(node);
		if (!init_cmp(node) && node->red_node == NULL)
		{
			get_ms()->f_or_nf = 1;
			ft_handle_parse_err(get_ms());
			return (1);
		}
		if (node->left && ((node->left->type == TOKEN_AND && get_ms()->exit != 0)
				|| (node->left->type == TOKEN_OR && get_ms()->exit == 0)))
			dodge_cmd(&node);
		else
		{
			get_ms()->exit = exec_cmd(&node, env);
			if (get_ms()->exit == ENO_CRITICAL && get_ms()->parent == TRUE)
			{
				ft_clean_ms();
				exit (1);
			}
			if (get_ms()->exit == ENO_CRITICAL)
				return (ENO_CRITICAL);
			dodge_cmd(&node);
		}
		// NEED TO CHECK FOR CRITICAL ERROR (WHAT ABOUT SUBSHELLS?)
	}
	return (get_ms()->exit);
}
