/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wildcards_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:26:04 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/20 16:58:32 by skapersk         ###   ########.fr       */
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

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i + 1])
		i++;
	return (i);
}

void	ft_swap(char **a, char **b)
{
	char	*stock;

	stock = *a;
	*a = *b;
	*b = stock;
}

int	name_cmp(char *file1, char *file2)
{
	int	i;

	i = 0;
	while (file1[i] && file2[i])
	{
		if (ft_toupper(file1[i]) != ft_toupper(file2[i]))
			return (ft_toupper(file1[i]) - ft_toupper(file2[i]));
		i++;
	}
	if (ft_toupper(file1[i]) == ft_toupper(file2[i]))
		return (ft_strncmp(file2, file1, ft_strlen(file1) + 1));
	return (ft_toupper(file1[i]) - ft_toupper(file2[i]));
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
				ft_swap (&argv[i], &argv[j]);
		j++;
		}
	i++;
	}
	return (argv);
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
			{
				while (i)
				{
					free(ret[i]);
					ret[i--] = NULL;
				}
				return (NULL);
			}
			i++;
		}
		entry = readdir(dir);
	}
	do_closedir(dir);
	return (ft_sort_tab(ret, tab_size(ret) + 1));
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
