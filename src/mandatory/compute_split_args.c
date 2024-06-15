/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:17:33 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/15 11:58:46 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	*skip_words(char *str, int *i, int *count, char *tmp)
// {
// 	int	start;

// 	start = *i;
// 	if (*count == 0)
// 	{
// 		while (str[start] && str[start] != ' ')
// 			start++;
// 		tmp = ft_calloc(start - *i + 1, sizeof(char));
// 		if (!tmp)
// 			return (NULL);
// 	}
// 	while (str[*i] && str[*i] != ' ')
// 	{
// 		tmp[*count] = str[*i];
// 		*count += 1;
// 		*i += 1;
// 	}
// 	if (str[*i] != '\0')
// 		*i += 1;
// 	tmp[*count] = '\0';
// 	return (tmp);
// }

// char	*init_and_alloc(char *str, int *i, int *count, char quote)
// {
// 	int		start;
// 	char	*tmp;

// 	start = *i;
// 	if (*count == 0)
// 	{
// 		while (str[start] && !is_quotes(str[start], quote))
// 			start++;
// 		tmp = ft_calloc(start + 1 + 2, sizeof(char));
// 		if (!tmp)
// 			return (NULL);
// 	}
// 	else
// 		tmp = NULL;
// 	return (tmp);
// }

// char	*skip_quotes(char *str, int *i, int *count, char *tmp)
// {
// 	char	quote;

// 	quote = assign_quote(str[*i]);
// 	*i += 1;
// 	tmp = init_and_alloc(str, i, count, quote);
// 	if (!tmp)
// 		return (NULL);
// 	tmp[*count] = '"';
// 	*count += 1;
// 	while (str[*i] && !is_quotes(str[*i], quote))
// 	{
// 		tmp[*count] = str[*i];
// 		*count += 1;
// 		*i += 1;
// 	}
// 	if (str[*i] != '\0' && str[*i] != ' ')
// 	{
// 		tmp = skip_words(str, i, count, tmp);
// 		if (!tmp)
// 			return (NULL);
// 	}
// 	else if (str[*i] != '\0' && str[*i == ' '])
// 		*i += 1;
// 	tmp[*count] = '\0';
// 	return (tmp);
// }

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

// char	**ft_split_args(char *str, t_node *node)
// {
// 	char	**tmp;
// 	int		count;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	node->c_cmd->ac = countwords(str, ' ');
// 	tmp = ft_calloc(countwords(str, ' ') + 1, sizeof(char *));
// 	if (!tmp)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		count = 0;
// 		if (str[i] && str[i] != ' ' && !find_quotes(str[i]))
// 			tmp[j] = skip_words(str, &i, &count, tmp[j]);
// 		else if (str[i] && str[i] != ' ' && find_quotes(str[i]))
// 			tmp[j] = skip_quotes(str, &i, &count, tmp[j]);
// 		if (tmp[j] == NULL)
// 			return (free_split_args(tmp, j), NULL);
// 		j++;
// 	}
// 	tmp[j] = NULL;
// 	return (tmp);
// }

static	void	ft_skip_word(char const *s, size_t	*i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

static char	**ft_allocater(char const *s, char **strs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			ft_skip_word(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

static void	ft_words_filler(const char *s, char **strs, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (s[(*i)] && s[(*i)] != ' ')
	{
		if (s[(*i)] != '\'' && s[(*i)] != '"')
			strs[j][k++] = s[(*i)++];
		else
		{
			quotes = s[(*i)++];
			strs[j][k++] = quotes;
			while (s[(*i)] != quotes)
				strs[j][k++] = s[(*i)++];
			strs[j][k++] = s[(*i)++];
		}
	}
}

static char	**ft_filler(char const *s, char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != ' ')
		{
			ft_words_filler(s, strs, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

char	**ft_expander_split(char const *s, t_node *node)
{
	size_t		count;
	char		**strs;
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
	strs = ft_calloc(count + 1, sizeof(char *));
	tofree = strs;
	strs = ft_allocater(s, strs);
	if (!strs || !count)
		return (ft_big_free(tofree), NULL);
	return (ft_filler(s, strs));
}
