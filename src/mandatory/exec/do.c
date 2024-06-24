/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:45:50 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/27 19:46:00 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_pipe(int pipfd[2])
{
	if (pipe(pipfd) == -1)
	{
		perror("Erreur lors de la creatin du pipe");
		return (1);
	}
	return (0);
}

int	do_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Close error");
		return (-1);
	}
	return (0);
}

int	do_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("Erreur lors de dup2");
		return (1);
	}
	return (0);
}
