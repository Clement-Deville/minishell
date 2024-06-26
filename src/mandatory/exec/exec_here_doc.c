/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:00:11 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/26 11:32:21 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	process_heredoc(t_node *node, int tmp_fd)
{
	char	*line;

	line = get_next_line(node->red_node->here_doc);
	while (line != NULL)
	{
		ft_heredoc_expand(line, tmp_fd);
		free(line);
		line = get_next_line(node->red_node->here_doc);
	}
	return (0);
}

int	exec_here_doc(t_node *nodes)
{
	t_node	*tmp;
	int		returned;

	returned = 0;
	tmp = nodes;
	if (tmp == NULL)
		return (0);
	while (tmp)
	{
		if (tmp->red_node != NULL)
		{
			returned = ft_init_heredoc(tmp);
			if (returned)
				return (get_ms()->exit = returned, returned);
		}
		else if (tmp->sub != NULL)
		{
			returned = exec_here_doc(tmp->sub);
			if (returned)
				return (get_ms()->exit = returned, returned);
		}
		dodge_cmd(&tmp);
	}
	return (0);
}
