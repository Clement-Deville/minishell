/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:29:26 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/10 13:40:15 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_input(char *filename, t_node *node)
{
	int	fd;

	if (access(filename, R_OK) != 0)
	{
		node->pid = NO_FORK;
		node->status = 1;
		return (perror(filename), 0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			node->pid = NO_FORK;
			node->status = 1;
			return (perror(filename), 0);
		}
		return (perror("Open"), -1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (fd);
}

int	set_output(char *filename, t_node *node)
{
	int	fd;

	if (access(filename, W_OK) != 0 && errno != ENOENT)
	{
		node->pid = NO_FORK;
		node->status = 1;
		return (perror(filename), 0);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			node->pid = NO_FORK;
			node->status = 1;
			return (perror(filename), 0);
		}
		return (perror("Open"), -1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (fd);
}

int	set_output_append(char *filename, t_node *node)
{
	int	fd;

	if (access(filename, W_OK) != 0 && errno != ENOENT)
	{
		node->pid = NO_FORK;
		node->status = 1;
		return (perror(filename), 0);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			node->pid = NO_FORK;
			node->status = 1;
			return (perror(filename), 0);
		}
		return (perror("Open"), -1);
	}
	if (do_dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	if (do_close(fd) == -1)
		return (-1);
	return (fd);
}

int	set_input_here_doc(int fd)
{
	if (dup2(fd, 0) == -1)
		return (perror("Here doc"), -1);
	if (close(fd) == -1)
		return (perror("Here doc"), -1);
	return (0);
}

int	do_redirections(t_node *node)
{
	t_red_node	*tmp;
	int			status;

	if (node->red_node == NULL)
		return (0);
	status = 0;
	tmp = node->red_node;
	while (tmp)
	{
		if (tmp->type == NODE_HERE_DOC)
			status = set_input_here_doc(tmp->here_doc);
		else if (tmp->type == NODE_RED_IN)
			status = set_input(tmp->value, node);
		else if (tmp->type == NODE_RED_OUT)
			status = set_output(tmp->value, node);
		else if (tmp->type == NODE_APPEND)
			status = set_output_append(tmp->value, node);
		if (status == -1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
