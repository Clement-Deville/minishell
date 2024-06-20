/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:20:06 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/20 14:20:18 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_path(char *path)
{
	if (path != NULL)
		if (path[0] == '.' || path[0] == '/')
			return (TRUE);
	return (FALSE);
}

void	print_not_found(char *cmd)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

t_bool	is_a_dir(const char *path)
{
	struct stat	entity;

	stat(path, &entity);
	if (errno == EACCES || errno == ENOENT)
		return (FALSE);
	return (S_ISDIR(entity.st_mode));
}
