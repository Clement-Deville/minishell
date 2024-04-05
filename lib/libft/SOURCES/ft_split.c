/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:47:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static	char	**freetab(char **strs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	return (0);
}

static char	*createstr(const char *s, char c, int *index)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (dest);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	*index += i - 1;
	return (dest);
}

static int	countwords(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (s[0] != c && s[0])
		words++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			words++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!strs)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			strs[j] = createstr(&s[i], c, &i);
			if (!strs[j])
				return (freetab(strs, j));
			j++;
		}
		i++;
	}
	strs[j] = 0;
	return (strs);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	i;
// 	char	**strs;
// 	char *s = "";
// 	char c = 0;

// 	i = 0;
// 	strs = ft_split(s, c);

// 	while (strs[i])
// 	{
// 		printf("%s\n", strs[i]);
// 		free(strs[i]);
// 		i++;
// 	}
// 	free(strs);
// 	return (0);
// }
