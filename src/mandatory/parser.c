/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:39:20 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/10 19:04:18 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*create_node(t_node_type type)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	return (new);
}
#include <stdio.h>
void	ft_join_args(char **args, t_token *token)
{
	if (!*args)
	{
		*args = ft_strdup("");
		// if (!*args)
		// 	return ;
	}
	// printf("--%s--", *args);
	*args = ft_strjoin(*args, " ");
	*args = ft_strjoin(*args, token->value);
	// if (!*args)
	// 	return ;
}

t_node	*ft_simple_cmd(t_token *token, t_mini_env *ms)
{
	t_node	*node;

	(void)ms;
	node = create_node(NODE_CMD);
	if (!node)
		return (NULL);
	while (token && token->type == TOKEN_ELSE)
	{
		ft_join_args(&(node->args), token);
		token = token->next;
	}
	return (node);
}

t_node	*ft_parser(t_mini_env *ms)
{
	t_token	*curr_token;
	t_node	*node;

	curr_token = ms->tokens;
	node = ft_simple_cmd(curr_token, ms);
	ft_printf("%s", node->args);
	return (node);
}
