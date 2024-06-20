/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:06:39 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/20 16:31:37 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
