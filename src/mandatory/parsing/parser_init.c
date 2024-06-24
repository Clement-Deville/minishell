/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:31:03 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/20 15:29:20 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	return (node);
}

t_node	*ft_parser(t_mini_env *ms, int min_prec)
{
	t_node	*node;
	t_node	*result;
	int		tmp_sub;

	if (!ms->tokens || get_ms()->err.type)
		return (NULL);
	node = ft_start(ms, min_prec);
	if (!node)
		return (NULL);
	while (ms->tokens)
	{
		tmp_sub = ms->in_sub;
		result = ft_handle_tokens(ms, node, min_prec);
		if (result && (tmp_sub != ms->in_sub))
			return (result);
		result = ft_recursive_parse(ms, node, min_prec);
		if (result)
			return (result);
		if (get_ms()->err.type)
			return (NULL);
	}
	return (node);
}

void	init_parsing(t_mini_env *ms)
{
	t_token	*tmp;
	int		nb_prec;

	nb_prec = 0;
	tmp = ms->tokens;
	ms->nodes = ft_parser(ms, nb_prec);
	if (ms->tokens)
		ft_set_parse_err(E_SYNTAX);
	ms->tokens = tmp;
}
