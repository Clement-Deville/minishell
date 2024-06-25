/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:08 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/25 10:32:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_err	ft_check_exec(char *file, t_bool cmd)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_err){ENO_CANT_EXEC, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 0, NULL});
	}
	if (cmd)
		return ((t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, file});
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

static t_path	get_env_path(char *path, char *cmd)
{
	int		i;
	t_err	err;
	char	*cmd_path;
	char	*new;
	char	**split_path;

	split_path = ft_split(path, ':');
	if (!split_path)
		return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_MALLOC_FAIL, cmd}
			, NULL});
	i = 0;
	new = ft_strjoin("/", cmd);
	while (split_path[i])
	{
		cmd_path = ft_strjoin(split_path[i], new);
		if (!cmd_path)
			return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_MALLOC_FAIL, cmd}
				, NULL});
		err = ft_check_exec(cmd_path, TRUE);
		if (err.no == ENO_SUCCESS)
			return ((t_path){(t_err){ENO_SUCCESS, 42, cmd_path}, cmd_path});
		i++;
	}
	ft_big_free(split_path);
	return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
}

t_path	ft_get_path(char *cmd)
{
	char	*value;

	if (*cmd == '\0')
		return ((t_path){
			(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return ((t_path){ft_check_exec(cmd, FALSE), cmd});
	value = ft_str_find_env("PATH");
	if (value)
		return (get_env_path(value, cmd));
	return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, cmd}, NULL});
}
