/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:47:07 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/25 11:54:47 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_single(t_node **node, t_dblist **env)
{
	if (is_subshell(*node))
		return (exec_sub((*node), env));
	else if (is_not_a_cmd(*node) && !(*node)->sub)
		return (do_no_cmd(*node));
	else if (is_empty(*node))
		return (0);
	else if (is_builtin(*node))
		return (exec_builtin((*node), env));
	else
		return (exec_standard(node, env));
}

void	dodge_cmd(t_node **node)
{
	if (is_pipeline(*node))
	{
		while (is_pipe_cmd((*node)))
			(*node) = (*node)->next;
	}
	else
		(*node) = (*node)->next;
}

int	exec_cmd(t_node **node, t_dblist **env)
{
	int	status;

	if (is_pipeline(*node))
		status = exec_pipeline(node, env);
	else
		status = exec_single(node, env);
	return (status);
}

void	handle_critical_error(void)
{
	if (get_ms()->exit == ENO_CRITICAL)
	{
		if (get_ms()->parent == TRUE)
			exit(clean_and_exit (1));
		exit(clean_and_exit (ENO_CRITICAL));
	}
}

int	start_exec(t_node *node, t_dblist **env)
{
	int	status;

	status = 0;
	if (node == NULL)
		return (1);
	while (node)
	{
		check_signals();
		if (node->red_node != NULL && node->red_node->here_doc != 0)
		{
			get_ms()->exit = ft_heredoc_go_expand(node);
			handle_critical_error();
		}
		if (!init_cmp(node) && node->red_node == NULL)
			return (get_ms()->f_or_nf = 1, ft_handle_parse_err(get_ms()), 1);
		if (!(node->left && ((node->left->type == TOKEN_AND && get_ms()->exit)
					|| (node->left->type == TOKEN_OR && get_ms()->exit == 0))))
		{
			status = exec_cmd(&node, env);
			get_ms()->exit = status;
			handle_critical_error();
		}
		dodge_cmd(&node);
	}
	return (get_ms()->exit);
}
