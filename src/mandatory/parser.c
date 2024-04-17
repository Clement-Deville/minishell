/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:39:20 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/11 18:59:14 by skapersk         ###   ########.fr       */
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
		if (!*args)
			return ;
	}
	else
		*args = ft_strjoin(*args, " ");
	*args = ft_strjoin(*args, token->value);
	if (!*args)
		return ;
}

t_token_type	ft_get_ast_token(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (TOKEN_PIPE);
	else if (type == TOKEN_AND)
		return (TOKEN_AND);
	else if (type == TOKEN_OR)
		return (TOKEN_OR);
	else
		return (TOKEN_NULL);
}

t_token_type	ft_get_token_red(t_token_type type)
{
	if (type == TOKEN_RED_IN)
		return (TOKEN_RED_IN);
	else if (type == TOKEN_RED_OUT)
		return (TOKEN_RED_OUT);
	else if (type == TOKEN_HEREDOC)
		return (TOKEN_HEREDOC);
	else if (type == TOKEN_QPPEND)
		return (TOKEN_APPEND);
	else
		return (TOKEN_NULL);
}

t_node	*ft_simple_cmd(t_token *token, t_mini_env *ms)
{
	t_node	*node;

	(void)ms;
	node = create_node(NODE_CMD);
	if (!node)
		return (NULL);
	while (token && (token->type == TOKEN_ELSE
			|| token->type == ft_get_token_red(token->type)))
	{
		if (token->type == ft_get_type_red(token->type))
		{
			ft_printf("%d", token_type);
		}
		ft_join_args(&(node->args), token);
		token = token->next;
	}
	return (node);
}

t_node	*ft_parser(t_mini_env *ms)
{
	t_node	*prev;
	t_token	*curr_token;
	t_node	*next;
	int		i;

	curr_token = ms->tokens;
	i = 0;
	prev = ft_check_cmd(curr_token);
	while (curr_token)
	{
		if (curr_token->type == ft_get_ast_token(curr_token->type))
		{

			i++;
		}
		next = ft_parser(ms);
		if (!next)
			return (prev);
		prev = ft_join_nodes();
		if (!prev)
			return ("FREE", NULL);
	}
	return (prev);
}
