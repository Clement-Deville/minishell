/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:18:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/12 18:52:47 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_path(t_dblist *env)
{
	while (env)
	{
		if (ft_strncmp("PATH", ((t_variable *)(env->content))->name, 5) == 0)
			return (((t_variable *)(env->content))->value);
		env = env->next;
	}
	return (NULL);
}

char	**add_dir(char **split_path)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_path[i])
	{
		temp = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		if (split_path[i] == NULL)
		{
			split_path[i] = temp;
			ft_free("%s", split_path);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (split_path);
}

int	len(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (0);
	while (split[i])
		i++;
	return (i);
}

char	**add_cmd_to_path(char **split_path, const char *cmd)
{
	int		i;
	char	**complete_path;

	i = 0;
	complete_path = (char **)malloc(sizeof(char *) * (len(split_path) + 1));
	if (complete_path == NULL)
		return (perror("Malloc error"), NULL);
	complete_path[len(split_path)] = NULL;
	while (split_path[i])
	{
		complete_path[i] = ft_strjoin(split_path[i], cmd);
		if (complete_path[i] == NULL)
			return (ft_free("%s", complete_path), NULL);
		i++;
	}
	return (complete_path);
}

int	change_path(char **cmd, char *new_path)
{
	char	*temp;

	temp = *cmd;
	*cmd = ft_strdup(new_path);
	if (*cmd == NULL)
	{
		*cmd = temp;
		return (perror("Malloc error"), -1);
	}
	return (free(temp), 0);
}

char	**parse_path(t_dblist *env)
{
	char		**split_path;
	char		*cut;
	const char	*path;

	path = get_path(env);
	if (path == NULL)
	{
		cut = ft_strdup("");
		if (cut == NULL)
			return (perror("Malloc error"), NULL);
		split_path = (char **)malloc(sizeof(char *) * 2);
		if (split_path == NULL)
			return (free(cut), perror("Malloc error"), NULL);
		split_path[0] = cut;
		split_path[1] = NULL;
		return (add_dir(split_path));
	}
	else
	{
		cut = ft_strchr(path, '/');
		split_path = ft_split(cut, ':');
		if (split_path == NULL)
			return (perror("Malloc error"), NULL);
		return (add_dir(split_path));
	}
}
