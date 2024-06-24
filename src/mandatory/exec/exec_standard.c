/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_standard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:48:07 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 14:41:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec(char **cmd, char *env[])
{
	// IL FAUT TRANSFORMER LA LIST EN UN TAB POUR L'EXEC
	if (execve(cmd[0], cmd, env) == -1)
	{
		perror("Probleme a l'execution de la commande");
		return (1);
	}
	return (0);
}

int	do_wait(int pid)
{
	int	status;

	set_wait_signals();
	status = 0;
	if (waitpid(pid, &status, 0) == -1)
	{
		if (get_ms()->wait_interrupted == TRUE)
		{
			get_ms()->wait_interrupted = FALSE;
			return (do_wait(pid));
		}
		return (setup_signals(), perror("Wait error"), ENO_CRITICAL);
	}
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			get_ms()->signal_int = TRUE;
		if (WTERMSIG(status) == SIGQUIT)
			get_ms()->signal_quit = TRUE;
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	clean_and_exit(int exitno)
{
	ft_clean_ms();
	return (exitno);
}

int	exec_standard(t_node **node, t_dblist **env)
{
	int		access_status;
	int		pid;
	char	**tab_env;
	int		status;
	int		red_status;

	pid = fork();
	if (pid < 0)
		return (perror("Fork error"), ENO_CRITICAL);
	if (pid == 0)
	{
		set_child_signals();
		red_status = do_redirections(*node);
		if (red_status == -1)
			exit(clean_and_exit (ENO_CRITICAL));
		if (red_status)
			exit(clean_and_exit (1));
		access_status = check_for_path_access(&((*node)->c_cmd->expand[0]), *env);
		if (access_status == -1)
			exit(clean_and_exit (ENO_CRITICAL));
		if (access_status)
			exit(clean_and_exit (access_status));
		tab_env = list_to_tab(*env);
		if (tab_env == NULL)
			exit(clean_and_exit (1));
		status = exec((*node)->c_cmd->expand, tab_env);
		exit(clean_and_exit (status));
	}
	status = do_wait(pid);
	return (status);
}
