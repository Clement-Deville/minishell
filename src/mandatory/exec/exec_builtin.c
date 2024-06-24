/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:40:36 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 17:19:24 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(t_node *node, t_dblist **env)
{
	int		pid;
	int		status;
	char	**command;
	int		red_status;

	command = node->c_cmd->expand;
	node->silent = FALSE;
	pid = fork();
	if (pid < 0)
		return (perror("Fork error"), ENO_CRITICAL);
	if (pid == 0)
	{
		red_status = do_redirections(node);
		if (red_status == -1)
			exit (clean_and_exit(ENO_CRITICAL));
		if (red_status)
			exit (clean_and_exit(1));
		if (ft_strncmp(command[0], "echo", 6) == 0)
			if (do_echo(command))
				exit (clean_and_exit(1));
		if (ft_strncmp(command[0], "cd", 3) == 0)
			if (do_cd(node, env))
				exit (clean_and_exit(1));
		if (ft_strncmp(command[0], "export", 8) == 0)
			if (do_export(node, env))
				exit (clean_and_exit(1));
		if (ft_strncmp(command[0], "env", 4) == 0)
			if (do_env(node, *env))
				exit (clean_and_exit(1));
		if (ft_strncmp(command[0], "pwd", 4) == 0)
			if (do_pwd(node))
				exit (clean_and_exit(1));
		if (ft_strncmp(command[0], "unset", 7) == 0)
			if (do_unset(&command[1], env))
				exit (clean_and_exit(1));
		if (ft_strncmp(command[0], "exit", 6) == 0)
			if (do_exit(node))
				exit (clean_and_exit(1));
		exit (clean_and_exit(0));
	}
	status = do_wait(pid);
	node->silent = TRUE;
	if (ft_strncmp(command[0], "export", 8) == 0)
		if (do_export(node, env))
			return (1);
	if (ft_strncmp(command[0], "cd", 3) == 0)
		if (do_cd(node, env))
			return (1);
	if (ft_strncmp(command[0], "unset", 7) == 0)
		if (do_unset(&command[1], env))
			return (1);
	if (ft_strncmp(command[0], "exit", 6) == 0)
		if (do_exit(node))
			return (1);
	return (status);
}
