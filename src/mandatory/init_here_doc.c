/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:44:49 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/05 15:42:14 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	ft_clean_ms();
	exit(SIGINT);
}

int	ft_error_exe(int p[2], int *pid)
{
	//SETOFF
	// NEED TO HANDLE SIGNAL  ERPROPERLY
	// set_ignore_signals();
	waitpid(*pid, pid, 0);
	// setup_signals();
	close(p[1]);
	if (WIFEXITED(*pid))
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
		if (!line)
			break ;
		if (ft_is_delimiter(node->value, line))
			break ;
		if (!*quotes)
			ft_heredoc_expand(line, p[1]);
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
	}
	ft_clean_ms();
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
	int	p[2];
	int	pid;

	if (node == NULL)
		fprintf(stderr, "YOLO\n");
	if (node->red_node != NULL && node->red_node->value != NULL)
	{
		if (node->red_node->type == NODE_HERE_DOC)
		{
			if (limiter_quotes_check(node->red_node))
				return (0);
			pipe(p);
			pid = (fork());
			if (!pid)
				ft_heredoc(node->red_node, p);
			if (ft_error_exe(p, &pid))
				return (0);
			node->red_node->here_doc = p[0];
		}
	}
	return (1);
}
