/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:49:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/24 16:34:01 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_cd(char *directory, t_dblist **env)
{
	char	*pwd;
	char	*complete_pwd;

	if (directory == NULL)
		return (perror("Malloc error"), -1);
	if (chdir(directory) == -1)
		return (perror("Error when changing dir"), -1);
	pwd = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if (pwd == NULL)
		return (perror("Malloc error"), -1);
	if (getcwd(pwd, FILENAME_MAX) == NULL)
		return (perror("Getcwd error"), free(pwd), -1);
	complete_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (complete_pwd == NULL)
		return (perror("Malloc error"), -1);
	if (export_one(complete_pwd, env) == -1)
		return (free(complete_pwd), -1);
	return (free(complete_pwd), 0);
}
