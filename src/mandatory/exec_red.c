/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:24:03 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/21 10:10:52 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_out(t_red_node *node, int *status)
{
	int	fd;

	if (!node->value)
	{
		ft_printf("ERROR TO HANDLE");
		return (*status);
	}
	fd = open(node->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: permission denied:", 2);
		ft_putendl_fd(node->value, 2);
		*status = -1;
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	do_in(t_red_node *node, int *status)
{
	int	fd;

	if (!node->value)
	{
		ft_printf("ERROR TO HANDLE");
		return (*status);
	}
	fd = open(node->value, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: no such file or directory:", 2);
		ft_putendl_fd(node->value, 2);
		*status = -1;
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	do_append(t_red_node *node, int *status)
{
	int	fd;

	if (!node->value)
	{
		ft_printf("ERROR TO HANDLE");
		return (*status);
	}
	fd = open(node->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf("ERROR FD");
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}
