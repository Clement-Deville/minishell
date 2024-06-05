/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:41:16 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/05 15:51:47 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		return (ft_putnbr_fd(get_ms()->exit, fd), 2);
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
	if (check_quotes(str))
		return (0);
	return (1);
}
