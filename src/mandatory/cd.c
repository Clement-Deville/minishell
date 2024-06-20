/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:49:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 09:10:49 by cdeville         ###   ########.fr       */
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

char	*do_get_pwd(t_node *node)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if (pwd == NULL)
	{
		if (node->silent == FALSE)
			perror("Malloc error");
		return (NULL);
	}
	if (getcwd(pwd, FILENAME_MAX) == NULL)
	{
		if (node->silent == FALSE)
			perror("getcwd");
		return (free(pwd), NULL);
	}
	return (pwd);
}

int	set_old_pwd(t_node *node, t_dblist **env)
{
	char	*pwd;
	char	*complete_pwd;

	pwd = do_get_pwd(node);
	if (pwd == NULL)
		return (-1);
	complete_pwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	if (complete_pwd == NULL)
	{
		if (node->silent == FALSE)
			perror("Malloc error");
		return (-1);
	}
	if (export_one(complete_pwd, env, node->silent) == -1)
		return (free(complete_pwd), -1);
	return (free(complete_pwd), 0);
}

int	set_pwd(t_node *node, t_dblist **env)
{
	char	*pwd;
	char	*complete_pwd;

	pwd = do_get_pwd(node);
	if (pwd == NULL)
		return (-1);
	complete_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (complete_pwd == NULL)
	{
		if (node->silent == FALSE)
			perror("Malloc error");
		return (-1);
	}
	if (export_one(complete_pwd, env, node->silent) == -1)
		return (free(complete_pwd), -1);
	return (free(complete_pwd), 0);
}

int	do_cd(t_node *node, t_dblist **env)
{
	char	*directory;

	if (nbr_of_args(node->c_cmd->expand) > 1)
	{
		if (node->silent == FALSE)
			ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (set_old_pwd(node, env))
		return (-1);
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
	return (set_pwd(node, env));
}
