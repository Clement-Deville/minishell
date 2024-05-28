/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:25:19 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/16 19:21:43 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_pipe_child(t_node *node, int fd[2], int child, t_mini_env *ms, int i)
{
	int	status;

	if (child == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (child == 2)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	status = exec_node(node, ms, TRUE, i);
	ft_clean_ms();
	exit(status);
}

int	ft_exec_pipeline(t_node *node, t_mini_env *ms, int i)
{
	int	status;
	int	fd[2];
	int	pid;
	int	pid_next;

	pipe(fd);
	pid = fork();
	if (!pid)
		ft_exec_pipe_child(node, fd, 1, ms, 1);
	else
	{
		pid_next = fork();
		if (!pid_next)
			ft_exec_pipe_child(node->next, fd, 2, ms, i);
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid, &status, 0);
			waitpid(pid_next, &status, 0);
			return (ft_get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}
