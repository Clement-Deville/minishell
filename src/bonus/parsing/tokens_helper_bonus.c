/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:46:40 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/20 15:20:02 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\t')
		return (1);
	return (0);
}

t_token	*create_new_token(char *value, t_token_type type)
{
	t_token	*new;

	if (!value)
		return (NULL);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	return (new);
}

int	ft_is_char(char *str)
{
	if (!ft_strncmp(str, "&&", 2) || *str == ' ' || *str == '<'
		|| *str == '>' || *str == '|' || *str == '(' || *str == ')')
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

t_bool	ft_skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}
