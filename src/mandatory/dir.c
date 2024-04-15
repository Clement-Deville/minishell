/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:15:57 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/15 17:16:24 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_closedir(DIR *dir)
{
	if (closedir(dir) != 0)
		return (perror("closedir"), 2);
	return (0);
}

DIR	*do_opendir(void)
{
	char	*current_dir_name;
	DIR		*dir;

	current_dir_name = getcwd(NULL, 0);
	if (current_dir_name == NULL)
		return (perror("getcwd error"), NULL);
	dir = opendir(current_dir_name);
	if (dir == NULL)
		perror("Opendir");
	free(current_dir_name);
	return (dir);
}

