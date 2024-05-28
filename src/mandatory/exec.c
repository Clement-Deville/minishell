/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:47:07 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/28 15:44:51 by cdeville         ###   ########.fr       */
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

int	do_wait(int pid, int *status)
{
	if (waitpid(pid, status, 0) == 1)
		return (perror("Wait error"), ENO_CRITICAL);
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	if (WIFSIGNALED(*status))
		return (128 + WTERMSIG(*status));
	return (1);
}

int	exec_builtin(t_node *node, t_dblist **env)
{
	// A verfier

	int		pid;
	int		status;
	char	**command;


	command = node->c_cmd->expand;
	pid = fork();
	if (pid < 0)
		return (perror("Fork error"), ENO_CRITICAL);
	if (pid == 0)
	{
		if (do_redirections(node))
			exit (1);
		if (ft_strncmp(command[0], "echo", 6) == 0)
			if (do_echo(command))
				exit (1);
		if (ft_strncmp(command[0], "cd", 3) == 0)
			if (do_cd(command[1], env))
				exit (1);
		if (ft_strncmp(command[0], "export", 8) == 0)
			if (do_export(&command[1], env))
				exit (1);
		if (ft_strncmp(command[0], "env", 4) == 0)
			if (do_env(*env))
				exit (1);
		if (ft_strncmp(command[0], "pwd", 4) == 0)
			if (do_pwd())
				exit (1);
		if (ft_strncmp(command[0], "unset", 7) == 0)
			if (do_unset(&command[1], env))
				exit (1);
		if (ft_strncmp(command[0], "exit", 6) == 0)
			if (do_exit(command[1]))
				exit (1);
		// NEED TO FREE EVERYTHING BEFORE EXITING
		exit (0);
	}
	if (do_wait(pid, &status) == -1)
		return (ENO_CRITICAL);
	if (ft_strncmp(command[0], "cd", 3) == 0)
		if (do_cd(command[1], env))
			return (1);
	if (ft_strncmp(command[0], "export", 8) == 0)
		if (do_export(&command[1], env))
			return (1);
	if (ft_strncmp(command[0], "unset", 7) == 0)
		if (do_unset(&command[1], env))
			return (1);
	if (ft_strncmp(command[0], "exit", 6) == 0)
		if (do_exit(command[1]))
			return (1);
	return (status);
}

int	exec_standard(t_node **node, t_dblist **env)
{
	int		access_status;
	int		pid;
	char	**tab_env;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("Fork error"), ENO_CRITICAL);
	if (pid == 0)
	{
		if (do_redirections(*node))
			exit (1);
		access_status = check_for_path_access(&((*node)->c_cmd->expand[0]), *env);
		if (access_status == -1)
			exit (ENO_CRITICAL);
		if (access_status)
			exit (access_status);
		// NEED TO FREE EVERYTHING HERE
		tab_env = list_to_tab(*env);
		if (tab_env == NULL)
			exit (1);
		exit (exec((*node)->c_cmd->expand, tab_env));
	}
	if (do_wait(pid, &status) == ENO_CRITICAL)
		return (ENO_CRITICAL);
	return (status);
}

int	exec_subshell(t_node **node, t_dblist **env)
{
	int		pid;
	char	**tab_env;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("Fork error"), ENO_CRITICAL);
	if (pid == 0)
	{
		if (do_redirections(*node))
			exit (1);
		tab_env = list_to_tab(*env);
		if (tab_env == NULL)
			exit (1);
		exit (main_subshell(ft_strlen((*node)->sub_node->args), (*node)->sub_node->args, tab_env));
	}
	if (do_wait(pid, &status) == ENO_CRITICAL)
		return (ENO_CRITICAL);
	return (status);
	(void)node;
	(void)env;
	return (0);
}

t_bool	is_subshell(t_node *node)
{
	if ((node)->sub_node)
		return (TRUE);
	return (FALSE);
}

int	exec_single(t_node **node, t_dblist **env)
{
	if (is_builtin(*node))
		return (exec_builtin((*node), env));
	else if (is_subshell(*node))
		return (exec_subshell(node, env));
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
	int	exit_value;
	int	status;

	exit_value = 0;
	status = 0;
	if (node == NULL)
		return (1);
	while (node)
	{
		if (node->left && ((node->left->type == TOKEN_AND && status != 0)
				|| (node->left->type == TOKEN_OR && status == 0)))
			dodge_cmd(&node);
		else
		{
			status = exec_cmd(&node, env);
			dodge_cmd(&node);
		}
		int i;
		i = 0;
		fprintf(stderr, "Node: %d\n", ++i);
		// NEED TO CHECK FOR CRITICAL ERROR (WHAT ABOUT SUBSHELLS?)
	}
	return (status);
}
