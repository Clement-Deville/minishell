/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:07:48 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 11:40:42 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
