/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_handle_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:10:27 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/05 12:12:05 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_handle_arg(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dq_arg(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dollar(char *str, int *i)
{
	int			start;
	char		*arg;
	char		*env;

	*i += 1;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		*i += 1;
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		*i += 1;
		return (ft_itoa(get_ms()->exit));
	}
	else if (!ft_is_valid_arg(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && ft_is_valid_arg(str[*i]))
		*i += 1;
	arg = ft_substr(str, start, *i - start);
	env = ft_str_find_env(arg);
	if (!env)
		return (free(arg), ft_strdup(""));
	return (free(arg), ft_strdup(env));
}

char	*ft_handle_simple_quotes(char *str, int *i)
{
	int	start;

	start = *i;
	*i += 1;
	while (str[*i] && str[*i] != '\'')
		*i += 1;
	*i += 1;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_double_quotes(char *str, int *i)
{
	char	*new;

	new = ft_strdup("\"");
	if (!new)
		return (NULL);
	*i += 1;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			new = ft_strjoin(new, ft_handle_dollar(str, i));
			if (!new)
				return (NULL);
		}
		else
		{
			new = ft_strjoin(new, ft_handle_dq_arg(str, i));
			if (!new)
				return (NULL);
		}
	}
	*i += 1;
	return (ft_strjoin(new, "\""));
}
