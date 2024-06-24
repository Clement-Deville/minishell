/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:38:02 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 08:49:18 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_subshell(t_node *node)
{
	if ((node)->sub)
		return (TRUE);
	return (FALSE);
}

t_bool	is_not_a_cmd(t_node *node)
{
	if (node->c_cmd->expand == NULL)
		return (TRUE);
	return (FALSE);
}

t_bool	is_pipeline(t_node *node)
{
	if (node->rigth && node->rigth->type == TOKEN_PIPE)
		return (TRUE);
	return (FALSE);
}

t_bool	is_builtin(t_node *node)
{
	char	**command;

	if (node->c_cmd == NULL)
		return (FALSE);
	command = node->c_cmd->expand;
	if (ft_strncmp(command[0], "echo", 6) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "export", 8) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "unset", 7) == 0)
		return (TRUE);
	if (ft_strncmp(command[0], "exit", 6) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_empty(t_node *node)
{
	if (!node || !node->c_cmd || !node->c_cmd->expand
		|| !node->c_cmd->expand[0] )
		return (TRUE);
	return (FALSE);
}
