/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pre_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:16:27 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/20 16:25:24 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_handle_quotes(char *str, int *i)
{
	char	*temp;

	if (str[*i] == '\'')
		temp = ft_handle_simple_quotes(str, i);
	else if (str[*i] == '"')
		temp = ft_handle_double_quotes(str, i);
	else if (str[*i] == '$')
		temp = ft_handle_dollar(str, i);
	else
		temp = ft_handle_arg(str, i);
	return (temp);
}

char	*ft_expand_loop(char *str, char *tmp, int i)
{
	char	*new;
	char	*temp;

	while (str[i])
	{
		temp = ft_handle_quotes(str, &i);
		if (!temp)
			return (free(tmp), NULL);
		new = ft_strjoin(tmp, temp);
		free(temp);
		free(tmp);
		if (!new)
			return (NULL);
		tmp = new;
	}
	return (tmp);
}

char	*ft_cmd_pre_expand(char *str)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	return (ft_expand_loop(str, tmp, 0));
}
