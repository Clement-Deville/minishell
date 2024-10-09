/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:42:56 by cdeville          #+#    #+#             */
/*   Updated: 2024/10/09 17:33:05 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

	if ((access(filename, W_OK) != 0 && errno != ENOENT)
		|| !ft_strncmp(filename, "", 1))
		return (perror(filename), 1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (perror(filename), 1);
		return (perror("Open yo"), -1);
	}
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (0);
}

int	fake_set_output_append(char *filename)
{
	int	fd;

	if ((access(filename, W_OK) != 0 && errno != ENOENT)
		|| !ft_strncmp(filename, "", 1))
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

int	do_no_cmd(t_node *node)
{
	t_red_node	*tmp;
	int			status;

	if (node->red_node == NULL)
		return (0);
	status = 0;
	tmp = node->red_node;
	while (tmp)
	{
		if (!init_red_cmp(tmp))
			return (ENO_CRITICAL);
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
		tmp = tmp->next;
	}
	return (0);
}
