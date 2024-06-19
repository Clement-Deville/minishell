/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:49:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/19 14:12:09 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	change_to_home(t_node *node, t_dblist **env)
{
	char	*home_path;

	home_path = catch_value("HOME", *env);
	if (home_path == NULL)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	else
	{
		if (chdir(home_path) == -1)
		{
			if (node->silent == FALSE)
				perror("Error when changing dir");
			return (-1);
		}
	}
	return (0);
}

int	do_cd(t_node *node, t_dblist **env)
{
	char 	*directory;
	char	*pwd;
	char	*complete_pwd;
	char	*old_pwd;
	char	*complete_old;

	if (nbr_of_args(node->c_cmd->expand) > 1)
	{
		if (node->silent == FALSE)
			ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	old_pwd = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if (old_pwd == NULL)
	{
		if (node->silent == FALSE)
			perror("Malloc error");
		return (-1);
	}
	if (getcwd(old_pwd, FILENAME_MAX) == NULL)
	{
		if (node->silent == FALSE)
			if (node->silent == FALSE)
				perror("getcwd");
		return (free(old_pwd), -1);
	}
	complete_old = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	if (complete_old == NULL)
	{
		if (node->silent == FALSE)
			perror("Malloc error");
		return (-1);
	}
	// Need to add condition (if name exists)
	if (export_one(complete_old, env, node->silent) == -1)
		return (free(complete_old), -1);
	free(complete_old);
	directory = node->c_cmd->expand[1];
	if (directory == NULL)
	{
		return (change_to_home(node, env));
	}
	if (chdir(directory) == -1)
	{
		if (node->silent == FALSE)
		{
			ft_putstr_fd("cd: ", 2);
			perror(directory);
		}
		return (-1);
	}
	pwd = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if (pwd == NULL)
	{
		if (node->silent == FALSE)
			perror("Malloc error");
		return (-1);
	}
	if (getcwd(pwd, FILENAME_MAX) == NULL)
	{
		if (node->silent == FALSE)
			if (node->silent == FALSE)
				perror("getcwd");
		return (free(pwd), -1);
	}
	complete_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (complete_pwd == NULL)
	{
		if (node->silent == FALSE)
			perror("Malloc error");
		return (-1);
	}
	// NEED TO ALSO FREE OLDPWD
	// Need to add condition (if name exists)
	if (export_one(complete_pwd, env, node->silent) == -1)
		return (free(complete_pwd), -1);
	return (free(complete_pwd), 0);
}
