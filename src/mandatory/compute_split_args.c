/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:17:33 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/05 12:34:58 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*skip_words(char *str, int *i, int *count, char *tmp)
{
	int	start;

	start = *i;
	if (*count == 0)
	{
		while (str[start] && str[start] != ' ')
			start++;
		tmp = ft_calloc(start - *i + 1, sizeof(char));
		if (!tmp)
			return (NULL);
	}
	while (str[*i] && str[*i] != ' ')
	{
		tmp[*count] = str[*i];
		*count += 1;
		*i += 1;
	}
	if (str[*i] != '\0')
		*i += 1;
	tmp[*count] = '\0';
	return (tmp);
}

char	*skip_quotes(char *str, int *i, int *count, char *tmp)
{
	int		start;
	char	quote;

	quote = assign_quote(str[*i]);
	*i += 1;
	start = *i;
	if (*count == 0)
	{
		while (str[start] && !is_quotes(str[start], quote))
			start++;
		tmp = ft_calloc(start + 1 + 2, sizeof(char));
		if (!tmp)
			return (NULL);
	}
	tmp[*count] = '"';
	*count += 1;
	while (str[*i] && !is_quotes(str[*i], quote))
	{
		tmp[*count] = str[*i];
		*count += 1;
		*i += 1;
	}
	if (str[*i] != '\0' && str[*i] != ' ')
		tmp = skip_words(str, i, count, tmp);
	else if (str[*i] != '\0' && str[*i == ' '])
		*i += 1;
	tmp[*count] = '\0';
	return (tmp);
}

int	countwords(char *s, char c)
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

char	**allocate_split_args(char *str, t_node *node)
{
	char	**tmp;

	node->c_cmd->ac = countwords(str, ' ');
	tmp = ft_calloc(node->c_cmd->ac + 1, sizeof(char *));
	return (tmp);
}

char	**ft_split_args(char *str, t_node *node)
{
	char	**tmp;
	int		i;
	int		j;
	int		count;

	tmp = allocate_split_args(str, node);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			tmp[j] = process_word(str, &i, &count);
			if (!tmp[j])
				return (free_split_args(tmp, j));
			j++;
		}
		else
			i++;
	}
	tmp[j] = NULL;
	return (tmp);
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
// 		{
// 			while (j > 0)
// 				free(tmp[--j]);
// 			free(tmp);
// 			return (NULL);
// 		}
// 		j++;
// 	}
// 	tmp[j] = NULL;
// 	return (tmp);
// }
