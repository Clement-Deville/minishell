/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:22:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/20 11:19:28 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_red_node	*ft_create_red_node(t_token_type type, char *value)
{
	t_red_node	*new;

	new = ft_calloc(1, sizeof(t_red_node));
	if (!new)
		return (NULL);
	new->type = ft_get_red_type(type);
	new->value = ft_strdup(value);
	if (!new->value)
		return (ft_set_parse_err(E_MEMORY), NULL);
	return (new);
}

t_node	*ft_simple_cmd(t_mini_env *ms)
{
	t_node	*node;

	node = ft_new_node(NODE_CMD);
	if (!node)
		return (ft_set_parse_err(E_MEMORY), NULL);
	while (ms->tokens && (ms->tokens->type == TOKEN_ELSE
			|| ft_is_redir(ms->tokens->type)))
	{
		if (ft_is_redir(ms->tokens->type))
		{
			if (!ft_get_red_node(&(node->red_node), ms))
				return (NULL);
		}
		else if (ms->tokens && ms->tokens->type == TOKEN_ELSE)
		{
			if (!ft_join_args(&(node->cmd), ms->tokens))
				return (ft_set_parse_err(E_MEMORY), NULL);
			ms->tokens = ms->tokens->next;
		}
	}
	return (node);
}

t_node	*ft_start(t_mini_env *ms, int min_prec)
{
	t_node	*node;

	if (!ms->tokens || get_ms()->err.type)
		return (NULL);
	if (ft_get_node_type(ms->tokens->type)
		|| (ms->tokens->type == TOKEN_SUBSHELL_CLOSE))
		return (ft_set_parse_err(E_SYNTAX),
			get_ms()->tmp = ms->tokens, NULL);
	else if (ms->tokens->type == TOKEN_SUBSHELL_OPEN)
	{
		ms->in_sub += 1;
		ms->tokens = ms->tokens->next;
		if (!ft_check_subs(ms->tokens, min_prec))
			return (NULL);
		node = ft_new_node(NODE_CMD);
		if (!node)
			return (ft_set_parse_err(E_MEMORY), NULL);
		node->sub = ft_parser(ms, min_prec + 1);
		if (!node->sub)
			return (ft_set_parse_err(E_MEMORY), NULL);
		if (ms->tokens && ms->tokens->type == TOKEN_SUBSHELL_CLOSE)
			ms->tokens = ms->tokens->next;
		// if (ms->tokens && ft_is_redir(ms->tokens->type))
		// {
		// 	if (!ft_get_red_node(&(node->red_node), ms))
		// 		return (NULL);
		// }
		return (node);
	}
	else
		return (ft_simple_cmd(ms));
}

t_node	*ft_handle_tokens(t_mini_env *ms, t_node *node, int min_prec)
{
	if (ft_get_node_type(ms->tokens->type))
	{
		node->rigth = ms->tokens;
		ms->tokens = ms->tokens->next;
	}
	if (!ms->tokens || ft_get_node_type(ms->tokens->type))
		return (ft_set_parse_err(E_SYNTAX), get_ms()->tmp = node->rigth, NULL);
	if (ft_get_node_type(ms->tokens->type)
		|| (ms->tokens->type == TOKEN_SUBSHELL_CLOSE && min_prec > 0))
	{
		if (ms->tokens->type == TOKEN_SUBSHELL_CLOSE)
		{
			ms->in_sub -= 1;
			ms->tokens = ms->tokens->next;
		}
		node->next = NULL;
		return (node);
	}
	return (NULL);
}

t_node	*ft_recursive_parse(t_mini_env *ms, t_node *node, int min_prec)
{
	node->next = ft_parser(ms, min_prec);
	if (!node->next)
		return (NULL);
	node->next->left = node->rigth;
	node->next->prev = node;
	// if (ms->in_sub > 0)
	// {
	// 	// ms->in_sub -= 1;
	// 	return (node);
	// }
	return (node);
}
