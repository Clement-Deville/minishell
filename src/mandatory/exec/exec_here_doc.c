/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:00:11 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 18:17:54 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_tmp_file(int *tmp_fd)
{
	*tmp_fd = open("/tmp/tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*tmp_fd < 0)
		return (perror("open"), ENO_CRITICAL);
	return (0);
}

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

int	copy_to_final_heredoc(int tmp_fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	int		new_fd;

	new_fd = open("/tmp/final_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd < 0)
		return (perror("open"), close(tmp_fd), ENO_CRITICAL);
	bytes_read = read(tmp_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(new_fd, buffer, bytes_read) != bytes_read)
			return (perror("write"), close(new_fd),
				close(tmp_fd), ENO_CRITICAL);
		bytes_read = read(tmp_fd, buffer, sizeof(buffer));
	}
	if (bytes_read < 0)
		perror("read");
	close(new_fd);
	return (0);
}

int	finalize_heredoc(t_node *node)
{
	int	fd;

	fd = open("/tmp/final_heredoc", O_RDONLY);
	if (fd < 0)
		return (perror("open"), ENO_CRITICAL);
	node->red_node->here_doc = fd;
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
