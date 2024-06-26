/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:06:50 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/25 14:17:21 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_in_fd(char *line, int p[2])
{
	ft_putstr_fd(line, p[1]);
	ft_putstr_fd("\n", p[1]);
}

void	ft_heredoc(t_red_node *node, int p[2])
{
	char	*line;

	signal(SIGINT, ft_heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_is_delimiter(node->value, line))
		{
			if (!line)
				ft_exit_mess(node);
			break ;
		}
		else
			print_in_fd(line, p);
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

int	process_here_doc(t_red_node *tmp)
{
	int			p[2];
	int			returned;
	int			pid;

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
	return (0);
}
