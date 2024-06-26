/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:13:23 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/26 10:11:43 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_heredoc_go_expand(t_node *node)
{
	int	tmp_fd;

	if (node->red_node->here_doc < 0)
		return (ENO_CRITICAL);
	if (open_tmp_file(&tmp_fd) != 0)
		return (close(node->red_node->here_doc), ENO_CRITICAL);
	if (process_heredoc(node, tmp_fd) != 0)
		return (close(tmp_fd), close(node->red_node->here_doc), ENO_CRITICAL);
	close(node->red_node->here_doc);
	close(tmp_fd);
	tmp_fd = open("/tmp/tmp_heredoc", O_RDONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp_fd < 0)
		return (perror("open"), ENO_CRITICAL);
	if (copy_to_final_heredoc(tmp_fd) != 0)
		return (ENO_CRITICAL);
	close(tmp_fd);
	return (finalize_heredoc(node));
}
