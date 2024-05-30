/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:49:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/30 15:56:20 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_cd(t_node *node, t_dblist **env)
{
	char 	*directory;
	char	*pwd;
	char	*complete_pwd;

	directory = node->c_cmd->expand[1];
	if (directory == NULL)
		return (perror("Malloc error"), -1);
	if (chdir(directory) == -1)
	{
		if (node->silent == FALSE)
			perror("Error when changing dir");
		return (-1);
	}
	pwd = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if (pwd == NULL)
		return (perror("Malloc error"), -1);
	if (getcwd(pwd, FILENAME_MAX) == NULL)
	{
		if (node->silent == FALSE)
			perror("Getcwd error");
		return (free(pwd), -1);
	}
	complete_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (complete_pwd == NULL)
		return (perror("Malloc error"), -1);
	// Need to add condition (if name exists)
	if (export_one(complete_pwd, env) == -1)
		return (free(complete_pwd), -1);
	return (free(complete_pwd), 0);
}
