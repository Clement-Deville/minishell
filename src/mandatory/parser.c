/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:22:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/28 16:05:09 by cdeville         ###   ########.fr       */
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

int	ft_is_redir(t_token_type type)
{
	if (type == TOKEN_HERE_DOC || type == TOKEN_APPEND
		|| type == TOKEN_RED_IN || type == TOKEN_RED_OUT)
		return (1);
	return (0);
}

int	ft_join_args(char **args, t_token *token)
{
	if (!*args)
	{
		*args = ft_calloc(1, sizeof(char));
		if (!*args)
			return (0);
	}
	else
	{
		*args = ft_strjoin(*args, " ");
		if (!*args)
			return (ft_printf("ARGS TO FREE"), 0);
	}
	*args = ft_strjoin(*args, token->value);
	if (!*args)
		return (0);
	return (1);
}

t_red_type	ft_get_red_type(t_token_type type)
{
	if (type == TOKEN_RED_IN)
		return (NODE_RED_IN);
	else if (type == TOKEN_RED_OUT)
		return (NODE_RED_OUT);
	else if (type == TOKEN_HERE_DOC)
		return (NODE_HERE_DOC);
	else
		return (NODE_APPEND);
}

char	*ft_add_args(t_token_type node)
{
	if (node == TOKEN_RED_IN)
		return ("<");
	else if (node == TOKEN_RED_OUT)
		return (">");
	else if (node == TOKEN_HERE_DOC)
		return ("<<");
	else if (node == TOKEN_APPEND)
		return (">>");
	else
		return (NULL);
}

t_red_node	*ft_create_red_node(t_token_type type, char *value)
{
	t_red_node	*new;

	new = ft_calloc(1, sizeof(t_red_node));
	if (!new)
		return (NULL);
	new->type = ft_get_red_type(type);
	new->args = ft_add_args(type);
	new->value = ft_strdup(value);
	if (!new->value)
		return (ft_printf("PB AVEC t_red_node value"), NULL);
	return (new);
}

void ft_add_red_node(t_red_node **node, t_red_node *new)
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

	while (ms->tokens && ft_is_redir(ms->tokens->type))
	{
		red_type = ms->tokens->type;
		ms->tokens = ms->tokens->next;
		if (!ms->tokens || ms->tokens->type != TOKEN_ELSE)
			return (ft_printf("SYNTAX PB REDIR NODE"), 0);
		tmp_red = ft_create_red_node(red_type, ms->tokens->value);
		if (!tmp_red)
			return (ft_printf("PB MALLOC TMP RED"), 0);
		ft_add_red_node(node, tmp_red);
		ms->tokens = ms->tokens->next;
	}
	return (1);
}

t_node	*ft_simple_cmd(t_mini_env *ms)
{
	t_node	*node;

	node = ft_new_node(NODE_CMD);
	if (!node)
		return (ft_printf("PB MALLOC NODE_CMD"), NULL);
	while (ms->tokens && (ms->tokens->type == TOKEN_ELSE
			|| ft_is_redir(ms->tokens->type)))
	{
		if (ft_is_redir(ms->tokens->type))
		{
			if (!ft_get_red_node(&(node->red_node), ms))
				return (ft_printf("PB GET REDIR NODE"), NULL);
		}
		else if (ms->tokens && ms->tokens->type == TOKEN_ELSE)
		{
			if (!ft_join_args(&(node->cmd), ms->tokens))
				return (ft_printf("PB NODE CMD"), NULL);
			ms->tokens = ms->tokens->next;
		}
	}
	return (node);
}

int	ft_get_node_type(t_token_type type)
{
	if (type == TOKEN_AND)
		return (1);
	else if (type == TOKEN_OR)
		return (1);
	else if (type == TOKEN_PIPE)
		return (1);
	else
		return (0);
}

int	ft_check_subs(t_token *token)
{
	int 	count;
	t_token	*tmp;

	count = 1;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_SUBSHELL_OPEN)
			count++;
		else if (tmp->type == TOKEN_SUBSHELL_CLOSE)
		{
			count--;
			if (count < 0)
				return (ft_printf("ERROR : Parenthesis mismatch\n", 0));
		}
		tmp = tmp->next;
	}
	if (count != 0)
		return (ft_printf("ERROR : Parenthesis mismatch\n"), 0);
	return (1);
}

char	*ft_convert_args(t_mini_env *ms)
{
	char	*str;
	int		i;

	i = 1;
	str = NULL;
	while (ms->tokens)
	{
		if (ms->tokens->type == TOKEN_SUBSHELL_CLOSE)
			i--;
		else if (ms->tokens->type == TOKEN_SUBSHELL_OPEN)
			i++;
		if (ms->tokens->type == TOKEN_SUBSHELL_CLOSE && i == 0)
			return (str);
		if (!str)
			str = ft_strdup(ms->tokens->value);
		else
		{
			if (!ft_join_args(&str, ms->tokens))
				return (ft_printf("PB AVEC LES ARGS CMD"), NULL);
		}
		ms->tokens = ms->tokens->next;
	}
	return (NULL);
}

t_subs_node	*create_sub_node(t_mini_env *ms)
{
	t_subs_node	*node;

	node = ft_calloc(1, sizeof(t_subs_node));
	if (!node)
		return (NULL);
	node->args = ft_convert_args(ms);
	return (node);
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

t_node	*ft_start(t_mini_env *ms)
{
	t_node	*node;

	node = ft_new_node(NODE_CMD);
	if (!node)
		return (ft_printf("PB MALLOC NODE CMD"), NULL);
	if (ft_get_node_type(ms->tokens->type)
		|| ms->tokens->type == TOKEN_SUBSHELL_CLOSE)
		return (ft_printf("ERROR SYNTAX1"), NULL);
	else if (ms->tokens->type == TOKEN_SUBSHELL_OPEN)
	{
		ms->tokens = ms->tokens->next;
		if (!ft_check_subs(ms->tokens))
			return (ft_printf("PB SYNTAX SUB"), NULL);
		node->sub_node = create_sub_node(ms);
		if (!node)
			return (ft_printf("PB MALLOC SUB NODE"), NULL);
		ft_add_back_sub(&(node->sub_node), node->sub_node);
		ms->tokens = ms->tokens->next;
		return (node);
	}
	else
		return (ft_simple_cmd(ms));
}

t_node	*ft_parser(t_mini_env *ms)
{
	t_token	*tmp;
	t_node	*node;

	tmp = ms->tokens;
	if (!tmp)
		return (NULL);
	node = ft_start(ms);
	if (!node)
		return (NULL);
	node->left = NULL;
	node->prev = NULL;
	while (ms->tokens)
	{
		if (ft_get_node_type(ms->tokens->type))
		{
			node->rigth = ms->tokens;
			ms->tokens = ms->tokens->next;
		}
		if (!ms->tokens)
			return (ft_printf("SYNTAX ERROR BI OP"), NULL);
		else
		{
			node->next = ft_parser(ms);
			if (!node->next)
				return (NULL);
			node->next->left = node->rigth;
			node->next->prev = node;
		}
	}
	return (node);
}

t_node	*init_parsing(t_mini_env *ms)
{
	t_token	*tmp;
	t_node	*node;

	tmp = ms->tokens;
	node = ft_parser(ms);
	if (ms->tokens != NULL)
		return (ft_printf("PB PARSING"), node);
	else
		ms->tokens = tmp;
	ft_compute_cmds(node);
	return (node);
}
