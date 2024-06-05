/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_check_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:12:55 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/05 15:23:40 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_single_quotes(char *str, int *i)
{
	int	count;

	count = 0;
	if (str[*i] == '\'')
	{
		(*i)++;
		count++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
		{
			count++;
			(*i)++;
		}
	}
	return (count);
}

int	count_double_quotes(char *str, int *i)
{
	int	count;

	count = 0;
	if (str[*i] == '"')
	{
		(*i)++;
		count++;
		while (str[*i] && str[*i] != '"')
			(*i)++;
		if (str[*i] == '"')
		{
			count++;
			(*i)++;
		}
	}
	return (count);
}

void	set_error(int count, int count2)
{
	if (count % 2)
		ft_set_parse_err(E_QUOTES);
	else if (count2 % 2)
		ft_set_parse_err(E_DQUOTES);
}

int	check_quotes(char *str)
{
	int	i;
	int	count;
	int	count2;

	i = 0;
	count = 0;
	count2 = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		count += count_single_quotes(str, &i);
		count2 += count_double_quotes(str, &i);
		if (str[i] && str[i] != '\'' && str[i] != '"')
			i++;
	}
	set_error(count, count2);
	return ((count % 2) + (count2 % 2));
}
