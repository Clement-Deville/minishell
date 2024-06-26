/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:13:57 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 17:39:19 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_redir(t_token_type type)
{
	if (type == TOKEN_HERE_DOC || type == TOKEN_APPEND
		|| type == TOKEN_RED_IN || type == TOKEN_RED_OUT)
		return (1);
	return (0);
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
