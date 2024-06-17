/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:44:53 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/17 23:06:43 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*clean_node(char *str)
{
	int		i;
	int		j;
	int		dstsize;
	char	*tmp;
	char	*ret;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2])
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
			i += 2;
		else
			tmp[j++] = str[i++];
	}
	free(str);
	dstsize = ft_strlen(tmp) + 1;
	ret = ft_calloc(dstsize, sizeof(char));
	return (ft_strlcpy(ret, tmp, dstsize), free(tmp), ret);
}

char	**ft_expand(char *str, t_node *node)
{
	char	**global;
	char	*expanded;
	// int		i;

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
	// i = 0;
	// while (global[i])
	// {
	// 	global[i] = ft_strip_quotes(global[i]);
	// 	i++;
	// }
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

char	*cut_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	*new;
	char	quote;

	new = malloc(strlen(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (i < strlen(str) && str[i] != quote)
				new[j++] = str[i++];
			if (i < strlen(str) && str[i] == quote)
				i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	free(str);
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
	{
		free_node(node);
		return (0);
	}
	if (is_subshell(node))
		return (1);
	if (node->cmd != NULL)
		tmp = ft_expand(node->cmd, node);
	if (!tmp)
		return (ft_free_c_cmd_expand(tmp), 0);
	node->c_cmd->expand = ft_handle_wildcard(tmp, node);
	if (!node->c_cmd->expand)
	{
		free_node(node);
		return (0);
	}
	i = 0;
	while (node->c_cmd->expand[i])
	{
		node->c_cmd->expand[i] = ft_strip_quotes(node->c_cmd->expand[i]);
		i++;
	}
	return (1);
}

// void	ft_compute_cmds(t_node *node)
// {
// 	if (node == NULL || (node->cmd == NULL && node->sub == NULL
// 			&& node->red_node == NULL))
// 		return ;
// 	else if (node->sub != NULL)
// 	{
// 		ft_compute_cmds(node->sub);
// 		ft_compute_cmds(node->next);
// 		return ;
// 	}
// 	else if (node->red_node != NULL)
// 	{
// 		if (!ft_init_heredoc(node))
// 			return ;
// 	}
// 	init_cmp(node);
// 	ft_compute_cmds(node->next);
// }
