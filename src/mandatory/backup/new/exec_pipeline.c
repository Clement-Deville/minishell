/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:51:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/27 12:51:21 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_cmd_pipe(const char *path, char *const args[], char *envp[])
{
	if (execve(path, args, envp) == -1)
	{
		perror("Probleme a l'execution de la commande");
		return (1);
	}
	return (0);
}

void	free_commands(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].type != FLAG_END)
	{
		ft_free("%s", cmds[i].args);
		i++;
	}
	free(cmds);
}

t_bool	are_in_child(int pid1)
{
	if (pid1 == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_cmd_executable(t_command cmds)
{
	if (cmds.status == 0 && cmds.pid != NO_FORK)
		return (TRUE);
	else
		return (FALSE);
}

int	nbr_of_cmds(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].type != FLAG_END)
	{
		i++;
	}
	return (i);
}

void	init(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].type != FLAG_END)
	{
		cmds[i].pid = 0;
		cmds[i].status = 0;
		i++;
	}
}

int	do_pipe(int pipfd[2])
{
	if (pipe(pipfd) == -1)
	{
		perror("Erreur lors de la creatin du pipe");
		return (1);
	}
	return (0);
}

int	do_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Close error");
		return (-1);
	}
	return (0);
}

int	do_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("Erreur lors de dup2");
		return (1);
	}
	return (0);
}

int	connect_read(int *pipefd)
{
	if (do_close((pipefd - 2)[WRITE]) == -1)
		return (1);
	if (do_dup2((pipefd - 2)[READ], STDIN_FILENO) == -1)
		return (1);
	if (do_close((pipefd - 2)[READ]) == -1)
		return (1);
	return (0);
}

int	connect_write(int *pipefd)
{
	if (do_close(pipefd[READ]) == -1)
		return (1);
	if (do_dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		return (1);
	if (do_close(pipefd[WRITE]) == -1)
		return (1);
	return (0);
}

int	close_useless_fd(int *pipefd, int size)
{
	int	i;

	i = 0;
	if (size == 0)
		return (0);
	while (i < size - 1)
	{
		if (do_close((pipefd + (2 * i))[READ]) == -1)
			return (1);
		if (do_close((pipefd + (2 * i))[WRITE]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	close_parent(int *pipefd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (do_close((pipefd + (2 * i))[READ]) == -1)
			return (free(pipefd), 1);
		if (do_close((pipefd + (2 * i))[WRITE]) == -1)
			return (free(pipefd), 1);
		i++;
	}
	free(pipefd);
	return (0);
}

t_node	cmd_to_node(t_command *cmds)
{
	t_node	node;

	if (cmds->type == SUBSHELL)
	{
		node.sub_node = cmds->sub_node;
	}
	else
	{

	}

}

int	do_fork(t_command *cmds, int i, int *pipefd, t_dblist **env)
{
	char	**tab_env;
	t_node	node;

	cmds[i].pid = fork();
	if (cmds[i].pid < 0)
		return (free(pipefd), perror("Fork error"), 1);
	if (are_in_child(cmds[i].pid))
	{
		if (i > 0)
			if (connect_read(&pipefd[2 * i]) == 1)
				return (1);
		if (cmds[i + 1].type != FLAG_END)
			if (connect_write(&pipefd[2 * i]) == 1)
				return (1);
		if (close_useless_fd(pipefd, i) == 1)
			return (1);
		node = cmd_to_node(cmds);
		exit (exec_single());
	}
	return (0);
}
// char	**parse_path(char *envp[])
// {
// 	char		**split_path;
// 	char		*cut;
// 	const char	*path;

// 	path = get_path(envp);
// 	if (path == NULL)
// 	{
// 		cut = ft_strdup("");
// 		if (cut == NULL)
// 			return (perror("Malloc error"), NULL);
// 	}
// 	else
// 		cut = ft_strchr(path, '/');
// 	split_path = ft_split(cut, ':');
// 	if (split_path == NULL)
// 		return (perror("Malloc error"), NULL);
// 	split_path = add_dir(split_path);
// 	return (split_path);
// }

static int	allocate(int **pipefd, int nbr_of_cmds)
{
	*pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds));
	if (pipefd == NULL)
		return (perror("Error de malloc"), -1);
	return (0);
}

int	wait_for_all(t_command *cmds, int size)
{
	int	i;
	int	exit_value;

	i = 0;
	exit_value = 0;
	while (i <= size)
	{
		if (cmds[i].pid != NO_FORK
			&& waitpid(cmds[i].pid, &cmds[i].status, 0) == 1)
			return (perror("Wait error"), 1);
		if (cmds[i].pid != NO_FORK && WIFEXITED(cmds[i].status))
			exit_value = WEXITSTATUS(cmds[i].status);
		if (cmds[i].pid != NO_FORK && WIFSIGNALED(cmds[i].status))
			exit_value = 128 + WTERMSIG(cmds[i].status);
		if (cmds[i].pid == NO_FORK)
			exit_value = cmds[i].status;
		i++;
	}
	return (exit_value);
}

int	start_piping(t_command *cmds, t_dblist **env)
{
	int	i;
	int	*pipefd;

	i = -1;
	if (allocate(&pipefd, nbr_of_cmds(cmds)) != 0)
		return (1);
	while (cmds[++i].type != FLAG_END)
	{
		if (cmds[i + 1].type != FLAG_END && pipe(&pipefd[2 * i]) == -1)
			return (free(pipefd), perror("Pipe error"), 1);
		if (is_cmd_executable(cmds[i]))
		{
			if (do_fork(cmds, i, pipefd, env) == 1)
				return (free(pipefd), free_commands(cmds), 1);
		}
		else
			cmds[i].pid = NO_FORK;
	}
	if (close_parent(pipefd, --i) == 1)
		return (1);
	return (wait_for_all(cmds, i));
}

t_command	*parse(t_node **node)
{
	t_command	*cmds;
	t_node		*temp;
	int			i;

	i = 1;
	temp = *(node);
	while ((*node)->rigth && (*node)->rigth->type == TOKEN_PIPE)
	{
		(*node) = (*node)->next;
		i++;
	}
	cmds = (t_command *)malloc(sizeof(t_command) * (i + 1));
	if (cmds == NULL)
		return (perror("Malloc"), NULL);
	cmds[i].type = FLAG_END;
	i = 0;
	while (temp != *node)
	{
		if (temp->c_cmd && temp->c_cmd->expand)
		{
			cmds[i].args = temp->c_cmd->expand;
			cmds[i].type = COMMAND;
		}
		else if (temp->sub_node && temp->sub_node->args)
		{
			cmds[i].sub_node = temp->sub_node->args;
			cmds[i].type = SUBSHELL;
		}
		temp = temp->next;
		ft_printf("Command %d = %s\n", i + 1, cmds[i].args[0]);
		i++;
	}
	if (temp->c_cmd && temp->c_cmd->expand)
	{
		cmds[i].args = temp->c_cmd->expand;
		cmds[i].type = COMMAND;
	}
	else if (temp->sub_node && temp->sub_node->args)
	{
		cmds[i].sub_node = temp->sub_node->args;
		cmds[i].type = SUBSHELL;
	}
	ft_printf("Command %d = %s\n", i + 1, cmds[i].args[0]);
	init(cmds);
	return (cmds);
}

int	exec_pipeline(t_node **node, t_dblist **env)
{
	t_command	*cmds;
	int			status;

	ft_printf("Pipeline called\n");
	cmds = parse(node);
	if (cmds == NULL)
		return (ENO_CRITICAL);
	status = start_piping(cmds, env);
	free_commands(cmds);
	return (status);
	(void)node;
	(void)env;
}
