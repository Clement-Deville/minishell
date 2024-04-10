/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:46:40 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/10 10:12:43 by skapersk         ###   ########.fr       */
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

int	there_is_quotes(char *tmp)
{
	int	i;

	i = 0;
	if (tmp[i])
	{
		i++;
		if (tmp[0] == '\'')
		{
			while (tmp[i] && tmp[i] != '\'')
				i++;
		}
		else if (tmp[0] == '"')
		{
			while (tmp[i] && tmp[i] != '"')
				i++;
		}
	}
	if (!tmp[i])
		return (i - 1);
	return (i + 1);
}
