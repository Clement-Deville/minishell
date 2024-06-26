/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:13:23 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/26 12:13:04 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	there_is_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	ft_heredoc_go_expand(t_node *node)
{
	int			p[2];

	if (there_is_quotes(node->red_node->value))
		return (0);
	if (node->red_node->here_doc < 0)
		return (ENO_CRITICAL);
	pipe(p);
	if (process_heredoc(node, p[1]) != 0)
		return (close(p[0]), close(p[1]),
			close(node->red_node->here_doc), ENO_CRITICAL);
	close(node->red_node->here_doc);
	close(p[1]);
	node->red_node->here_doc = p[0];
	return (0);
}
