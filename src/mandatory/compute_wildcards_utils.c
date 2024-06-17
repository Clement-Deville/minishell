/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wildcards_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:26:04 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/17 17:45:36 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**no_asterisk(char *str)
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(str);
	if (!ret[0])
		return (NULL);
	return (ret);
}

int	ft_visible(char *entry)
{
	if (entry[0] == '.')
		return (0);
	return (1);
}

char	**there_asterisk(char *str, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**ret;

	dir = do_opendir();
	ret = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (patern_match(str, entry->d_name) && ft_visible(entry->d_name))
		{
			ret[i] = ft_strdup(entry->d_name);
			if (!ret[i])
				return (NULL);
			i++;
		}
		entry = readdir(dir);
	}
	do_closedir(dir);
	return (ret);
}

void	free_wildcards(t_wildcard *wildcard)
{
	t_wildcard	*temp;
	int			i;

	while (wildcard != NULL)
	{
		temp = wildcard;
		if (temp->files != NULL)
		{
			i = 0;
			while (temp->files[i] != NULL)
			{
				free(temp->files[i]);
				i++;
			}
			free(temp->files);
		}
		wildcard = wildcard->next;
		free(temp);
	}
}
