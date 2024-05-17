/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:46 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/17 11:14:10 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

int	ft_check_red(t_node *node)
{
	t_red_node	*r_node;
	int			status;

	r_node = node->red_node;
	while (r_node)
	{
		if (r_node->type == NODE_RED_OUT
			&& do_out(r_node, &status) != ENO_SUCCESS)
			return (status);
		else if (r_node->type == NODE_RED_IN
			&& do_out(r_node, &status) != ENO_SUCCESS)
			return (status);
		else if (r_node->type == NODE_APPEND
			&& do_append(r_node, &status) !=ENO_SUCCESS)
			return (status);
		else if (r_node->type == NODE_HERE_DOC)
			(dup2(r_node->here_doc, 0), close(r_node->here_doc));
		r_node = r_node->next;
	}
	return (ENO_SUCCESS);
}

void	ft_set_stds(t_bool piped, t_mini_env *ms)
{
	if (piped)
		return ;
	dup2(ms->stdin, 0);
	dup2(ms->stdout, 1);
}

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	ft_exec_child(t_node *node, t_mini_env *ms)
{
	t_path	path_status;
	int		status;
	int		fork_pid;

	fork_pid = fork();
	if (!fork_pid)
	{
		status = ft_check_red(node);
		if (status != ENO_SUCCESS)
		{
			ft_clean_ms();
			exit(status);
		}
		path_status = ft_get_path((node->c_cmd->expand)[0]);
		if (path_status.err.no != ENO_SUCCESS)
		{
			status = ft_err_msg(path_status.err);
			ft_clean_ms();
			exit(status);
		}
		if (execve(path_status.path, node->c_cmd->expand,
				ms->env) == -1)
		{
			ft_clean_ms();
			exit(1);
		}
	}
	waitpid(fork_pid, &status, 0);
	return (ft_get_exit_status(status));
}

int	exec_simple_cmd(t_node *node, t_mini_env *ms, t_bool piped)
{
	int	status;

	if (!node->c_cmd->expand)
	{
		status = ft_check_red(node);
		return (ft_set_stds(piped, ms), (status && ENO_GENERAL));
	}
	else if (ft_is_builtin((node->c_cmd->expand)[0]))
	{
		status = ft_check_red(node);
		if (status != ENO_SUCCESS)
			return (ft_set_stds(piped, ms), ENO_GENERAL);
		status = ft_exec_builtin(node->c_cmd->expand);
		return (ft_set_stds(piped, ms), status);
	}
	else
		return (ft_exec_child(node, ms));
}

int	exec_subshell(t_node *node, t_mini_env *ms)
{
	int		status;
	int		fork_pid;
	int		ac;
	char	**env;

	ms->line = node->sub_node->args;
	ac = ft_strlen(ms->line);
	env = ms->env;
	fork_pid = fork();
	if (!fork_pid)
	{
		main_subshell(ac, &ms->line, env);
	}
	waitpid(fork_pid, &status, 0);
	return (ft_get_exit_status(status));
}

int	exec_node(t_node *node, t_mini_env *ms, t_bool piped, int i)
{
	int	status;

	if (node->next && (node->rigth && node->rigth->type == TOKEN_PIPE) && i == 0)
	{
		status = ft_exec_pipeline(node, ms, 0);
		return (status);
	}
	else if (node->next && node->rigth->type == TOKEN_OR)
	{
		status = exec_simple_cmd(node, ms, FALSE);
		if (status == ENO_SUCCESS)
			return (status);
		return (exec_node(node->next, ms, FALSE, 0));
	}
	else if (node->next && node->rigth->type == TOKEN_AND)
	{
		status = exec_simple_cmd(node, ms, FALSE);
		if (status == ENO_SUCCESS)
			return (exec_node(node->next, ms, FALSE, 0));
		return (status);
	}
	else if (node->sub_node != NULL)
	{
		status = exec_subshell(node, ms);
		if (status == ENO_SUCCESS)
			return (exec_node(node->next, ms, FALSE, 0));
		return (status);
	}
	else
	{
		return (exec_simple_cmd(node, ms, piped));
	}
	return (ENO_GENERAL);
}

void	start_exec(t_node *node, t_mini_env *ms)
{
	if (!node)
		return ;
	else
		ms->exit = exec_node(node, ms, FALSE, 0);
}
