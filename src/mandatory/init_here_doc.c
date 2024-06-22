/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:44:49 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/22 11:07:46 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	ft_clean_ms();
	exit(128 + SIGINT);
}

int	ft_error_exe(int p[2], int pid)
{
	int status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1)
		return (setup_signals(), close(p[1]), 130);
	if (close(p[1]) == -1)
		return (perror("close"), ENO_CRITICAL);
	setup_signals();
	if (WEXITSTATUS(status) == 2)
		return (WEXITSTATUS(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (0);
	return (1);
}

void	ft_heredoc(t_red_node *node, int p[2])
{
	char	*line;
	char	*quotes;

	signal(SIGINT, ft_heredoc_sigint_handler);
	quotes = node->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_is_delimiter(node->value, line))
			break ;
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
		free(line);
	}
	ft_clean_ms();
	if (close(p[0]) == -1 || close(p[1]) == -1)
	{
		perror("close");
		exit (1);
	}
	exit(0);
}

int	limiter_quotes_check(t_red_node *node)
{
	char	*quotes;

	quotes = node->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	if (*quotes == '"' || *quotes == '\'')
	{
		if (!ft_check_here_quotes(quotes))
			return (1);
	}
	return (0);
}

int	ft_init_heredoc(t_node *node)
{
	int			p[2];
	int			pid;
	t_red_node	*tmp;
	int			returned;

	tmp = node->red_node;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			if (tmp->type == NODE_HERE_DOC)
			{
				if (limiter_quotes_check(tmp))
					return (0);
				pipe(p);
				pid = fork();
				if (pid < 0)
					return (perror("Fork error"), ENO_CRITICAL);
				if (!pid)
					ft_heredoc(tmp, p);
				returned = ft_error_exe(p, pid);
				if (returned)
					return (close(p[0]), returned);
				tmp->here_doc = p[0];
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
