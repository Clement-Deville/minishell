/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:14:33 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/21 12:21:52 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_node(t_node *node)
{
	node->c_cmd = ft_calloc(1, sizeof(t_compute_cmd));
	if (!node->c_cmd)
		return (0);
	node->c_cmd->ac = 0;
	node->c_cmd->av = NULL;
	node->c_cmd->wildcard = ft_calloc(1, sizeof(t_wildcard));
	if (!node->c_cmd->wildcard)
		return (0);
	node->c_cmd->expand = NULL;
	node->c_cmd->redir = NULL;
	return (1);
}

int	ft_is_valid_arg(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_str_find_env(char *arg)
{
	t_dblist	*envlst;

	envlst = get_ms()->envlst;
	while (envlst)
	{
		if (!ft_strncmp(arg, ((t_variable *)envlst->content)->name,
				ft_strlen(arg) + 1))
			return (((t_variable *)envlst->content)->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	ft_big_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->c_cmd)
	{
		if (node->c_cmd->av)
			ft_big_free(node->c_cmd->av);
		if (node->c_cmd->expand)
			ft_big_free(node->c_cmd->expand);
		if (node->c_cmd->wildcard)
			free(node->c_cmd->wildcard);
		free(node->c_cmd);
	}
	free(node);
}
