/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_re_node_wildcards.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:20:53 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/18 16:32:09 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_in_quotes(char *str);

char	*ft_expand_red_wildcard(char *str)
{
	int				i;
	char			*ret;
	char			**ret2;

	i = do_asterisk(str);
	if (i > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (NULL);
	}
	else if ((!ft_contains_asterisk(str) || !i) || is_in_quotes(str))
	{
		ret = ft_strdup(str);
		if (!ret)
			return (NULL);
	}
	else
	{
		ret2 = there_asterisk(str, i);
		if (!ret2)
			return (NULL);
		else
			return (*ret2);
	}
	return (ret);
}
char	*ft_red_handle_wildcard(char *glob)
{
	char		*new;

	new = ft_calloc(1, sizeof(char));
	if (!new)
		return (free(glob), NULL);
	new = ft_expand_red_wildcard(glob);
	if (!new)
		return (free(glob), NULL);
	return (free(glob), new);
}

int	init_red_cmp(t_red_node *node)
{
	char	*tmp;
	char	*expanded;

	tmp = NULL;
	if (node == NULL)
		return (0);
	tmp = ft_cmd_pre_expand(node->value);
	if (!tmp)
		return (0);
	expanded = ft_red_handle_wildcard(tmp);
	if (!expanded)
		return (0);
	node->value = ft_strip_quotes(expanded);
	if (!node->value)
		return (0);
	return (1);
}

