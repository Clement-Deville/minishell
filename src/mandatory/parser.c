/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:39:20 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/18 11:16:00 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*convert_type2(t_red_type type)
{
	if (type == NODE_RED_IN)
		return ("NODE_RED_IN");
	else if (type == NODE_RED_OUT)
		return ("NODE_RED_OUT*");
	else if (type == NODE_HERE_DOC)
		return ("NODE_HERE_DOC");
	else
		return ("TOKEN_NULL");
}

char	*convert_type(t_node_type type)
{
	if (type == NODE_CMD)
		return ("NODE_CMD");
	else if (type == NODE_PIPE)
		return ("NODE_PIPE");
	else if (type == NODE_AND)
		return ("NODE_AND");
	else if (type == NODE_OR)
		return ("NODE_OR");
	else
		return ("TOKEN_NULL");
}

char	*convert(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_AND)
		return ("TOKEN_AND");
	else if (type == TOKEN_OR)
		return ("TOKEN_OR");
	else
		return ("TOKEN_NULL");
}

t_node	*create_node(t_node_type type)
{
	t_node	*new;
	// ft_printf("====== %s =====\n", convert_type(type));
	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	return (new);
}
#include <stdio.h>
int	ft_join_args(char **args, t_token *token)
{
	if (!*args)
	{
		*args = ft_strdup("");
		if (!*args)
			return (0);
	}
	else
		*args = ft_strjoin(*args, " ");
	*args = ft_strjoin(*args, token->value);
	if (!*args)
		return (0);
	return (1);
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
	else if (type == TOKEN_HERE_DOC)
		return (TOKEN_HERE_DOC);
	else if (type == TOKEN_APPEND)
		return (TOKEN_APPEND);
	else
		return (TOKEN_NULL);
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

t_red_node	*create_red_node(t_token_type type, char *value)
{
	t_red_node	*new;

	new = ft_calloc(1, sizeof(t_red_node));
	if (!new)
		return (NULL);
	new->type = ft_get_red_type(type);
	new->value = ft_strdup(value);
	// new->args = convert_type(type);
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

int		ft_is_red_node(t_red_node **node, t_mini_env *ms)
{
	t_token_type	red_type;
	t_red_node		*tmp_red;

	while (ms->tokens && ft_get_token_red(ms->tokens->type))
	{
		red_type = ms->tokens->type;
		ms->tokens = ms->tokens->next;
		if (!ms->tokens /*|| ms->tokens->type != TOKEN_ELSE*/)
			return (ft_printf("ERROR SYNTAX --> TOKEN RED"), 0);
		tmp_red = create_red_node(red_type, ms->tokens->value);
		if (!tmp_red)
			return (ft_printf("ERREUR : create red node"), 0);
		ft_add_red_node(node, tmp_red); // penser a verif si le add_red a pas echoue
		ms->tokens = ms->tokens->next;
	}
	return (1);
}

t_node	*ft_simple_cmd(t_token *token, t_mini_env *ms)
{
	t_node	*node;

	(void)ms;
	if (!token)
		return (NULL);
	node = create_node(NODE_CMD);
	if (!node)
		return (NULL);
	while (token && (token->type == TOKEN_ELSE
			|| token->type == ft_get_token_red(token->type)))
	{
		if (token->type == ft_get_token_red(token->type))
		{
			if (!ft_is_red_node(&(node->red_node), ms))
				return(ft_printf("ERROR ft_is_red_node"), NULL);
		}
		else if (token && token->type == TOKEN_ELSE)
		{
			if (!ft_join_args(&(node->args), token))
			{
				ft_printf("PB AVEC LES ARGS CMD");
				return (NULL);
			}
		}
		token = token->next;
		ms->tokens = token;
	}
	return (node);
}

int	check_parentheses(t_token *token)
{
	int	count;
	t_token	*tmp;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_SUBSHELL_OPEN)
			count++;
		else if (tmp->type == TOKEN_SUBSHELL_CLOSE)
		{
			count--;
			if (count < 0)
			{
				printf("ERROR : Parenthesis mismatch\n");
				return (0);
			}
		}
		tmp = tmp->next;
	}
	if (count != 0)
	{
		printf("ERROR : Parenthesis mismatch\n");
		return (0);
	}
	return (1);
}

t_node	*ft_check_cmd(t_token *token, t_mini_env *ms, int *i)
{
	t_node	*next;

	if (!token)
		return (NULL);
	if (token->type == ft_get_ast_token(token->type) || token->type == TOKEN_SUBSHELL_CLOSE)
	{
		ft_printf("ERROR --> !! A GERER !!");
		return (NULL);
	}
	else if (token && token->type == TOKEN_SUBSHELL_OPEN)
	{
		token = token->next;
		ms->tokens = token;
		*i += 1;
		next = ft_parser(ms, i, token);
		if (!next)
			return (NULL);
		// printf("**%s  --- %s**\n", ms->tokens->value, token->value);
		if (ms->tokens == NULL || ms->tokens->type != TOKEN_SUBSHELL_CLOSE)
		{
			ft_printf("%s", "ERROR SYNTAX");
			return (NULL);
		}
		ms->tokens = ms->tokens->next;
	}
	else
		next = ft_simple_cmd(token, ms);
	return (next);
}

t_node_type	ft_get_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (NODE_PIPE);
	else if (type == TOKEN_AND)
		return (NODE_AND);
	else
		return (NODE_OR);
}

t_node	*ft_parser(t_mini_env *ms, int *i, t_token *curr_token)
{
	t_node	*prev;
	t_node	*node;
	t_node	*next;

	if (*i == 0)
	{
		if (!check_parentheses(curr_token))
			return (NULL);
	}
	prev = ft_check_cmd(curr_token, ms, i);
	if (!prev)
		return (NULL);
	curr_token = ms->tokens;
	if (!curr_token)
		return (prev);
	if ((curr_token->type == TOKEN_SUBSHELL_CLOSE && *i >= 1))
	{
		*i -= 1;
		if (*i >= 0)
			return (prev);
		else
		{
			printf("ERROR )");
			return (free(prev), NULL);
		}
	}
	while (curr_token && curr_token->type == ft_get_ast_token(curr_token->type))
	{
		node = create_node(ft_get_type(curr_token->type));
		ft_join_args(&(node->args), curr_token);
		curr_token = curr_token->next;
		ms->tokens = ms->tokens->next;
		if (!curr_token)
		{
			ft_printf("SYNTAX2ERROR");
			return (NULL);
		}
		next = ft_parser(ms, i, curr_token);
		if (!node)
			return (prev);
		node->prev = prev;
		node->next = next;
		//prev = ft_join_nodes();
		// if (!prev)
			// return (free(prev), NULL);
	}
	return (node);
}
