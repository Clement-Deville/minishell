/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:23:10 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/13 16:06:20 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_expand_wildcard(char *str, t_node *node)
{
	int				i;
	char			**ret;

	i = do_asterisk(str);
	node->c_cmd->ac += i;
	if (!ft_contains_asterisk(str) || !i)
	{
		ret = no_asterisk(str);
		if (!ret)
			return (NULL);
	}
	else
	{
		ret = there_asterisk(str, i);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

char	**ft_join_wildcard(t_node *node)
{
	int			j;
	int			k;
	char		**joined;
	t_wildcard	*wildcard;

	joined = ft_calloc(node->c_cmd->ac + 2, sizeof(char *));
	if (!joined)
		return (NULL);
	k = 0;
	wildcard = node->c_cmd->wildcard;
	while (wildcard->next != NULL)
	{
		j = 0;
		while (wildcard->files[j])
		{
			joined[k] = ft_strdup(wildcard->files[j]);
			if (!joined[k])
				return (NULL);
			j++;
			k++;
		}
		wildcard = wildcard->next;
	}
	joined[k] = NULL;
	return (joined);
}

char	**ft_handle_wildcard(char **glob, t_node *node)
{
	int			i;
	char		**new;
	t_wildcard	*wildcard;

	i = 0;
	wildcard = node->c_cmd->wildcard;
	while (glob[i])
	{
		wildcard->next = ft_calloc(1, sizeof(t_wildcard));
		if (!wildcard->next)
			return (NULL);
		wildcard->files = ft_expand_wildcard(glob[i], node);
		if (!wildcard->files)
			return (NULL);
		wildcard = wildcard->next;
		i++;
	}
	wildcard->next = NULL;
	new = ft_join_wildcard(node);
	if (!new)
		return (ft_big_free(glob), NULL);
	return (ft_big_free(glob), new);
}
