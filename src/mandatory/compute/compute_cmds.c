/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:44:53 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/20 16:52:44 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*process_quotes(char *str, char *tmp)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			tmp[j++] = str[i++];
			while (str[i] && str[i] != quote)
				tmp[j++] = str[i++];
			if (str[i] == quote)
				tmp[j++] = str[i++];
		}
		else
			tmp[j++] = str[i++];
	}
	return (tmp);
}

char	*clean_node(char *str)
{
	char	*tmp;
	char	*ret;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2])
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = process_quotes(str, tmp);
	if (!tmp)
		return (NULL);
	free(str);
	ret = ft_strdup(tmp);
	free(tmp);
	if (!ret)
		return (NULL);
	return (ret);
}

char	**ft_expand(char *str, t_node *node)
{
	char	**global;
	char	*expanded;

	expanded = NULL;
	expanded = ft_cmd_pre_expand(str);
	if (!expanded)
		return (NULL);
	expanded = clean_node(expanded);
	if (!expanded)
		return (NULL);
	global = ft_expander_split(expanded, node);
	free(expanded);
	if (!global)
		return (NULL);
	return (global);
}

char	*remove_quotes_from_str(char *str)
{
	int		j;
	int		k;
	char	*new;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	j = 0;
	k = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '"')
		{
			j++;
			continue ;
		}
		new[k++] = str[j++];
	}
	new[k] = '\0';
	return (new);
}

int	init_cmp(t_node *node)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	if (node == NULL)
		return (0);
	if (!init_node(node))
		return (free_node(node), 0);
	if (is_subshell(node))
		return (1);
	if (node->cmd != NULL)
		tmp = ft_expand(node->cmd, node);
	if (!tmp)
		return (ft_free_c_cmd_expand(tmp), 0);
	node->c_cmd->expand = ft_handle_wildcard(tmp, node);
	if (!node->c_cmd->expand)
		return (free_node(node), 0);
	i = 0;
	while (node->c_cmd->expand[i])
	{
		node->c_cmd->expand[i] = ft_strip_quotes(node->c_cmd->expand[i]);
		i++;
	}
	return (1);
}
