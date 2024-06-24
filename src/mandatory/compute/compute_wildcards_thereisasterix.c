/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wildcards_thereisasterix.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:10:29 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 11:33:34 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	**ft_sort_tab(char **argv, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i <= size - 1)
	{
		j = i + 1;
		while (j <= size - 1)
		{
			if (name_cmp(argv[i], argv[j]) > 0)
				ft_swap(&argv[i], &argv[j]);
		j++;
		}
	i++;
	}
	return (argv);
}

void	read_entry(DIR *dir, char *str, char **ret)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (patern_match(str, entry->d_name) && ft_visible(entry->d_name))
		{
			ret[i] = ft_strdup(entry->d_name);
			if (!ret[i])
			{
				perror("malloc");
				while (i)
				{
					free(ret[i]);
					ret[i--] = NULL;
				}
				return ;
			}
			i++;
		}
		entry = readdir(dir);
	}
}

char	**there_asterisk(char *str, int i)
{
	DIR				*dir;
	char			**ret;

	dir = do_opendir();
	ret = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (perror("calloc"), NULL);
	read_entry(dir, str, ret);
	if (!ret)
		return (NULL);
	do_closedir(dir);
	return (ft_sort_tab(ret, tab_size(ret) + 1));
}
