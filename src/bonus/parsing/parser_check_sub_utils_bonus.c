/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_sub_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:19:32 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/26 19:27:00 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*find_next_head(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_SUBSHELL_OPEN)
			return (token);
		token = token->next;
	}
	return (NULL);
}

t_token	*find_next_close(t_token **token)
{
	while (*token)
	{
		if ((*token)->type == TOKEN_SUBSHELL_CLOSE)
			return (*token);
		if ((*token)->type == TOKEN_SUBSHELL_OPEN)
		{
			*token = (*token)->next;
			if (find_next_close(token) == NULL)
				return (NULL);
		}
		*token = (*token)->next;
	}
	return (NULL);
}
