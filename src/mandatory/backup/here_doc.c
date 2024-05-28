/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:43:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/27 19:43:41 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_stdin(char *limiter, int *pipefd)
{
	char	*line;

	if (do_close(pipefd[READ]) == -1)
		exit (1);
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			exit (1);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			if (do_close(STDIN_FILENO) == -1)
				exit (1);
			get_next_line(STDIN_FILENO);
			if (line == NULL)
				exit (1);
			break ;
		}
		ft_putstr_fd(line, pipefd[WRITE]);
		free(line);
	}
	exit (0);
}

int	connect_here_doc(int pid, int *pipefd)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (perror("Wait error"), -1);
	if (do_close(pipefd[WRITE]) == -1)
		return (-1);
	if (do_dup2(pipefd[READ], STDIN_FILENO) == -1)
		return (-1);
	if (do_close(pipefd[READ]) == -1)
		return (-1);
	if (WIFEXITED(status) == 0)
		return (-1);
	if (WEXITSTATUS(status) == 1)
		return (-1);
	return (0);
}

int	set_input_here_doc(char *limiter)
{
	int		pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("Error pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Error fork"), -1);
	if (pid == 0)
		read_stdin(limiter, pipefd);
	if (pid > 0)
		if (connect_here_doc(pid, pipefd) == -1)
			return (-1);
	return (0);
}
