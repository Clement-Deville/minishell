/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_split_args_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:19:09 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/05 12:34:36 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_quotes(char c, char x)
{
	if (c == x)
		return (1);
	return (0);
}

char	assign_quote(char c)
{
	char	quote;

	if (c == '\'')
		quote = '\'';
	else
		quote = '"';
	return (quote);
}

char	*process_word(char *str, int *i, int *count)
{
	char	*word;

	if (!find_quotes(str[*i]))
		word = skip_words(str, i, count, NULL);
	else
		word = skip_quotes(str, i, count, NULL);
	return (word);
}

char	**free_split_args(char **tmp, int j)
{
	while (j > 0)
		free(tmp[--j]);
	free(tmp);
	return (NULL);
}
