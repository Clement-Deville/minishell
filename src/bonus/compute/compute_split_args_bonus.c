/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:17:33 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 12:40:29 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	countwords(const char *s, char c)
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

static void	ft_words_filler(const char *s, char **str, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (s[(*i)] && s[(*i)] != ' ')
	{
		if (s[(*i)] != '\'' && s[(*i)] != '"')
			str[j][k++] = s[(*i)++];
		else
		{
			quotes = s[(*i)++];
			str[j][k++] = quotes;
			while (s[(*i)] != quotes)
				str[j][k++] = s[(*i)++];
			str[j][k++] = s[(*i)++];
		}
	}
}

static char	**ft_filler(char const *s, char **str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && str[j])
	{
		if (s[i] != ' ')
		{
			ft_words_filler(s, str, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (str);
}

char	**ft_expander_split(char const *s, t_node *node)
{
	size_t		count;
	char		**str;
	char		**tofree;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	node->c_cmd->ac = countwords(s, ' ');
	while (s[i])
	{
		if (s[i] != ' ' && ++count)
			ft_skip_word(s, &i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	str = ft_calloc(count + 1, sizeof(char *));
	tofree = str;
	str = ft_allocater(s, str);
	if (!str)
		return (ft_big_free(tofree), NULL);
	return (ft_filler(s, str));
}
