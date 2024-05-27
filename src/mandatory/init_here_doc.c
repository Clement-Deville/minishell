/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:44:49 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/20 19:40:51 by skapersk         ###   ########.fr       */
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
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, NULL);
	// g_minishell.signint_child = 0;
	close(p[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (1);
	return (0);
}

int	ft_is_delimiter(char *str, char *line)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			str++;
			continue ;
		}
		else if (*str == *line)
		{
			str++;
			line++;
		}
		else
			return (0);
	}
	while (*str == '"' || *str == '\'')
		str++;
	return (!*str);
}

static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*ft_garbage(void *str, t_bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(str));
		return (str);
	}
}

int	ft_heredoc_handle_dollar(char *str, int i, int fd)
{
	int		start;
	char	*tmp;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(987987, fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = ft_garbage(ft_substr(str, start, i), FALSE);
		tmp = ft_str_find_env(tmp);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
	return (i - 1);
}

void	ft_heredoc_expand(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += ft_heredoc_handle_dollar(str, i, fd);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}

int	ft_check_here_quotes(char *str)
{
	if(!check_quotes(str + 1))
	{
		ft_printf("PB QUOTES NOT CLOSED --> TO FREE");
		return (0);
	}
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
	if (*quotes == '"' || *quotes == '\'')
	{
		if (!ft_check_here_quotes(quotes))
		{
			ft_clean_ms();
			exit(1);
		}
	}
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

void	ft_init_heredoc(t_node *node)
{
	int	p[2];
	int	pid;

	if (node->red_node != NULL && node->red_node->value != NULL)
	{
		if (node->red_node->type == NODE_HERE_DOC)
		{
			pipe(p);
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				ft_heredoc(node->red_node, p);
			if (!ft_error_exe(p, &pid))
				return ;
			node->red_node->here_doc = p[0];
		}
	}
}
