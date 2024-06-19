/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:20:21 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/19 20:38:47 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*ft_new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->cmd = NULL;
	new_node->left = NULL;
	new_node->rigth = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->red_node = NULL;
	return (new_node);
}

int	ft_join_args(char **args, t_token *token)
{
	char	*tmp;

	tmp = NULL;
	if (!*args)
	{
		tmp = ft_calloc(1, sizeof(char));
		if (!tmp)
			return (ft_big_free(args), ft_clear_token(token), 0);
		free(*args);
	}
	else
	{
		tmp = ft_strjoin(*args, " ");
		if (!tmp)
			return (ft_big_free(args), ft_clear_token(token), 0);
		free(*args);
	}
	*args = ft_strjoin(tmp, token->value);
	free(tmp);
	if (!*args)
		return (0);
	return (1);
}

void	ft_add_red_node(t_red_node **node, t_red_node *new)
{
	t_red_node	*curr_node;

	if (!*node)
	{
		*node = new;
		return ;
	}
	curr_node = *node;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new;
}

int	ft_get_red_node(t_red_node **node, t_mini_env *ms)
{
	t_token_type	red_type;
	t_red_node		*tmp_red;
	t_token			*tmp;

	while (ms->tokens && ft_is_redir(ms->tokens->type))
	{
		red_type = ms->tokens->type;
		tmp = ms->tokens;
		ms->tokens = ms->tokens->next;
		if (!ms->tokens || ms->tokens->type != TOKEN_ELSE)
			return (ft_set_parse_err(E_SYNTAX), get_ms()->tmp = tmp, 0);
		if ( ms->tokens->type != TOKEN_ELSE)
			return (ft_set_parse_err(E_SYNTAX),
				get_ms()->tmp = ms->tokens->next, 0);
		tmp_red = ft_create_red_node(red_type, ms->tokens->value);
		if (!tmp_red)
			return (ft_set_parse_err(E_MEMORY), 0);
		ft_add_red_node(node, tmp_red);
		ms->tokens = ms->tokens->next;
	}
	return (1);
}

void	ft_add_back_sub(t_subs_node **lst, t_subs_node *new)
{
	t_subs_node	*curr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}
