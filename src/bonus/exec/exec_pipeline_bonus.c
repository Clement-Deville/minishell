/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:51:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/25 09:31:06 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_fork(t_node **node, int i, int *pipefd, t_dblist **env)
{
	int	status;

	status = 0;
	(*node)->pid = fork();
	if ((*node)->pid < 0)
		return (perror("Fork error"), 1);
	if (are_in_child((*node)->pid))
	{
		get_ms()->parent = FALSE;
		if (i > 0)
			if (connect_read(&pipefd[2 * i]) == 1)
				return (free(pipefd), 1);
		if (is_pipe_cmd((*node)->next))
			if (connect_write(&pipefd[2 * i]) == 1)
				return (free(pipefd), 1);
		if (close_useless_fd(pipefd, i) == 1)
			return (free(pipefd), 1);
		free(pipefd);
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
	exit_value = 0;
	head = (*node);
	while (i <= size)
	{
		if ((*node)->pid != NO_FORK)
		{
			exit_value = do_wait((*node)->pid);
			if (exit_value == -1)
				return (perror("Wait error"), ENO_CRITICAL);
		}
		if ((*node)->pid == NO_FORK)
			exit_value = (*node)->status;
		(*node) = (*node)->next;
		i++;
	}
	(*node) = head;
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
	return (close_and_wait(node, i, pipefd));
}
