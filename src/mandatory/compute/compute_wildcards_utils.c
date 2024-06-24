/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wildcards_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:26:04 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 12:30:14 by skapersk         ###   ########.fr       */
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
