/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:51:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 11:41:07 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	wait_for_all(t_node **node, int size)
{
	int		i;
	int		exit_value;
	t_node	*head;

	i = 0;
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

int	close_and_wait(t_node **node, int i, int *pipefd)
{
	if (close_parent(pipefd, --i) == 1)
		return (ENO_CRITICAL);
	return (wait_for_all(node, i));
}

int	init_piping(t_node **node, int i, int **pipefd)
{
	if (i && !init_cmp(*node) && (*node)->red_node == NULL)
		return (free(*pipefd), ENO_CRITICAL);
	if (is_pipe_cmd((*node)->next) && pipe(&(*pipefd)[2 * i]) == -1)
		return (free(*pipefd), perror("Pipe error"), ENO_CRITICAL);
	if ((*node)->status == -1)
		return (free(*pipefd), ENO_CRITICAL);
	return (0);
}

int	exec_pipeline(t_node **node, t_dblist **env)
{
	int		i;
	int		*pipefd;
	t_node	*head;

	i = 0;
	head = *node;
	init(*node);
	if (allocate(&pipefd, nbr_of_cmds(*node)) != 0)
		return (ENO_CRITICAL);
	while (is_pipe_cmd(*node))
	{
		if (init_piping(node, i, &pipefd) == ENO_CRITICAL)
			return (ENO_CRITICAL);
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
	return (close_and_wait(node, i, pipefd));
}
