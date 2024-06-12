/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:16:12 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/12 18:44:25 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <minishell.h>

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

int	check_command_access(const char *path)
{
	if (access(path, R_OK) == 0)
		if (access(path, X_OK) == 0)
			return (0);
	if (errno == EACCES)
		return (CANT_EXEC);
	if (errno == ENOENT)
		return (DONOT_EXIST);
	else
		return (128);
}

int	check_for_all(char **paths, char **cmd)
{
	int		i;
	int		access_status;
	char	*access_denied_path;

	i = 0;
	access_denied_path = NULL;
	if (cmd && *cmd[0] == 0)
		return (print_not_found(""), -1);
	while (paths[i])
	{
		access_status = check_command_access(paths[i]);
		if (access_status == 0)
			return (change_path(cmd, paths[i]));
		if (access_status == CANT_EXEC)
			access_denied_path = paths[i];
		i++;
	}
	if (access_denied_path)
	{
		access_status = check_command_access(access_denied_path);
		return (perror(access_denied_path), access_status);
	}
	if (access_status != 0)
		print_not_found(*cmd);
	return (access_status);
}

int	check_for_path_access(char **cmd, t_dblist *env)
{
	char	**paths;
	char	**complete_paths;
	int		access_status;

	if (is_path(*cmd) == TRUE)
	{
		access_status = check_command_access(*cmd);
		if (access_status != 0)
			perror(*cmd);
		return (access_status);
	}
	else
	{
		paths = parse_path(env);
		if (paths == NULL)
			return (-1);
		complete_paths = add_cmd_to_path(paths, *cmd);
		ft_free("%s", paths);
		if (complete_paths == NULL)
			return (-1);
		access_status = check_for_all(complete_paths, cmd);
		ft_free("%s", complete_paths);
		return (access_status);
	}
}
