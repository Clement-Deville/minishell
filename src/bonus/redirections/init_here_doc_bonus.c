/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:44:49 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 18:10:15 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	ft_clean_ms();
	exit(128 + SIGINT);
}

int	ft_error_exe(int p[2], int pid)
{
	int	status;

	status = 0;
	set_ignore_signals();
	if (waitpid(pid, &status, 0) == -1)
		return (perror("wait"), setup_signals(), close(p[1]), 1);
	if (close(p[1]) == -1)
		return (perror("close"), ENO_CRITICAL);
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	ft_exit_mess(t_red_node *node)
{
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(node->value, 2);
	ft_putstr_fd("')\n", 2);
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
	t_red_node	*tmp;
	int			returned;

	returned = 0;
	tmp = node->red_node;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			if (tmp->type == NODE_HERE_DOC)
			{
				returned = process_here_doc(tmp);
				if (returned)
					return (returned);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
