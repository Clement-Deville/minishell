/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:51:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/19 18:39:27 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_cmd_pipe(const char *path, char *const args[], char *envp[])
{
	if (execve(path, args, envp) == -1)
	{
		perror("Probleme a l'execution de la commande");
		return (1);
	}
	return (0);
}

t_bool	are_in_child(int pid1)
{
	if (pid1 == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_cmd_executable(t_node *node)
{
	if (node->status == 0 && node->pid != NO_FORK)
		return (TRUE);
	else
		return (FALSE);
}

t_bool	is_pipe_cmd(t_node *node)
{
	if (!node)
		return (FALSE);
	if ((node->left && node->left->type == TOKEN_PIPE)
		|| (node->rigth && node->rigth->type == TOKEN_PIPE))
		return (TRUE);
	return (FALSE);
}

int	nbr_of_cmds(t_node *node)
{
	int	i;

	i = 0;
	while (is_pipe_cmd(node))
	{
		node = node->next;
		i++;
	}
	return (i);
}

void	init(t_node *node)
{
	while (is_pipe_cmd(node))
	{
		node->pid = 0;
		node->status = 0;
		node = node->next;
	}
}

int	connect_read(int *pipefd)
{
	if (do_close((pipefd - 2)[WRITE]) == -1)
		return (1);
	if (do_dup2((pipefd - 2)[READ], STDIN_FILENO) == -1)
		return (1);
	if (do_close((pipefd - 2)[READ]) == -1)
		return (1);
	return (0);
}

int	connect_write(int *pipefd)
{
	if (do_close(pipefd[READ]) == -1)
		return (1);
	if (do_dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		return (1);
	if (do_close(pipefd[WRITE]) == -1)
		return (1);
	return (0);
}

int	close_useless_fd(int *pipefd, int size)
{
	int	i;

	i = 0;
	if (size == 0)
		return (0);
	while (i < size - 1)
	{
		if (do_close((pipefd + (2 * i))[READ]) == -1)
			return (1);
		if (do_close((pipefd + (2 * i))[WRITE]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	close_parent(int *pipefd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (do_close((pipefd + (2 * i))[READ]) == -1)
			return (free(pipefd), 1);
		if (do_close((pipefd + (2 * i))[WRITE]) == -1)
			return (free(pipefd), 1);
		i++;
	}
	free(pipefd);
	return (0);
}

int	do_fork(t_node **node, int i, int *pipefd, t_dblist **env)
{
	int	status;

	status = 0;
	(*node)->pid = fork();
	if ((*node)->pid < 0)
		return (free(pipefd), perror("Fork error"), 1);
	if (are_in_child((*node)->pid))
	{
		get_ms()->parent = FALSE;
		if (i > 0)
			if (connect_read(&pipefd[2 * i]) == 1)
				return (1);
		if (is_pipe_cmd((*node)->next))
			if (connect_write(&pipefd[2 * i]) == 1)
				return (1);
		if (close_useless_fd(pipefd, i) == 1)
			return (1);
		status = exec_single(node, env);
		ft_clean_ms();
		exit (status);
	}
	return (0);
}

// int	do_fork(t_node **node, int i, int *pipefd, t_dblist **env)
// {
// 	(*node)->pid = fork();
// 	if ((*node)->pid < 0)
// 		return (free(pipefd), perror("Fork error"), 1);
// 	if (are_in_child((*node)->pid))
// 	{
// 		if (i > 0)
// 			if (connect_read(&pipefd[2 * i]) == 1)
// 				return (1);
// 		if (is_pipe_cmd((*node)->next))
// 			if (connect_write(&pipefd[2 * i]) == 1)
// 				return (1);
// 		if (close_useless_fd(pipefd, i) == 1)
// 			return (1);
// 		exit (exec_single(node, env));
// 	}
// 	return (0);
// }
// char	**parse_path(char *envp[])
// {
// 	char		**split_path;
// 	char		*cut;
// 	const char	*path;

// 	path = get_path(envp);
// 	if (path == NULL)
// 	{
// 		cut = ft_strdup("");
// 		if (cut == NULL)
// 			return (perror("Malloc error"), NULL);
// 	}
// 	else
// 		cut = ft_strchr(path, '/');
// 	split_path = ft_split(cut, ':');
// 	if (split_path == NULL)
// 		return (perror("Malloc error"), NULL);
// 	split_path = add_dir(split_path);
// 	return (split_path);
// }

static int	allocate(int **pipefd, int nbr_of_cmds)
{
	*pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds));
	if (pipefd == NULL)
		return (perror("Error de malloc"), -1);
	return (0);
}

int	wait_for_all(t_node **node, int size)
{
	int		i;
	int		exit_value;
	t_node	*head;

	i = 0;
	//SETOFF
	set_ignore_signals();
	exit_value = 0;
	head = (*node);
	while (i <= size)
	{
		if ((*node)->pid != NO_FORK
			&& waitpid((*node)->pid, &((*node)->status), 0) == -1)
			return (setup_signals(), perror("Wait error"), ENO_CRITICAL);
		if ((*node)->pid != NO_FORK && WIFEXITED((*node)->status))
			exit_value = WEXITSTATUS((*node)->status);
		if ((*node)->pid != NO_FORK && WIFSIGNALED((*node)->status))
			exit_value = 128 + WTERMSIG((*node)->status);
		if ((*node)->pid == NO_FORK)
			exit_value = (*node)->status;
		(*node) = (*node)->next;
		i++;
	}
	// si un process retourne ENO CRITICAL FAUT IL ATTENDRE TOUS LES PROCESSES?
	(*node) = head;
	setup_signals();
	return (exit_value);
}

int	start_piping(t_node **node, t_dblist **env)
{
	int		i;
	int		*pipefd;
	t_node	*head;

	i = 0;
	head = *node;
	if (allocate(&pipefd, nbr_of_cmds(*node)) != 0)
		return (ENO_CRITICAL);
	while (is_pipe_cmd(*node))
	{
		if (i)
		{
			if (!init_cmp(*node) && (*node)->red_node == NULL)
				return (free(pipefd), ENO_CRITICAL);
		}
		if (is_pipe_cmd((*node)->next) && pipe(&pipefd[2 * i]) == -1)
			return (free(pipefd), perror("Pipe error"), ENO_CRITICAL);
		if ((*node)->status == -1)
			return (free(pipefd), ENO_CRITICAL);
		if (is_cmd_executable((*node)))
		{
			if (do_fork(node, i, pipefd, env) == 1)
				return (free(pipefd), ENO_CRITICAL);
		}
		else
			(*node)->pid = NO_FORK;
		(*node) = (*node)->next;
		i++;
	}
	(*node) = head;
	if (close_parent(pipefd, --i) == 1)
		return (ENO_CRITICAL);
	return (wait_for_all(node, i));
}

int	exec_pipeline(t_node **node, t_dblist **env)
{
	int			status;

	init(*node);
	// t_node	*test;
	// test = (*node);
	// while(is_pipe_cmd(test))
	// {
	// 	printf("ARG : %s\n", test->c_cmd->expand[0]);
	// 	test = test->next;
	// }
	// t_node	*test;
	// test = (*node);
	// while (is_pipe_cmd(test))
	// {
	// 	printf("Is pipe\n");
	// 	test = test->next;
	// }
	status = start_piping(node, env);
	return (status);
	(void)status;
	return (0);
	(void)node;
	(void)env;
}
