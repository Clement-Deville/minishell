/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:37 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/26 19:23:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*set_tmp(t_token *token)
{
	if (token->next)
		return (token->prev);
	else
		return (token);
}

int	recursive_sub_track(t_token **token)
{
	t_token	*tmp;
	t_token	*next_head;

	tmp = set_tmp(*token);
	next_head = find_next_head(*token);
	while (*token)
	{
		if ((*token)->type == TOKEN_SUBSHELL_CLOSE
			&& (*token)->prev->type == TOKEN_SUBSHELL_CLOSE
			&& (*tmp).next->type == TOKEN_SUBSHELL_OPEN && next_head
			&& next_head->type == tmp->next->type)
			if (find_next_close(&next_head) == (*token))
				return (0);
		if ((*token)->type == TOKEN_SUBSHELL_CLOSE)
			return (1);
		if ((*token)->type == TOKEN_SUBSHELL_OPEN)
		{
			*token = (*token)->next;
			if (recursive_sub_track(token) == 0)
				return (0);
		}
		*token = (*token)->next;
	}
	return (1);
}

int	sub_in_sub_error(t_token *token, int min_prec)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (min_prec > 0)
		return (1);
	tmp = token->prev;
	tmp2 = token->prev;
	if (!recursive_sub_track(&tmp))
		return (ft_set_parse_err(E_SYNTAX),
			get_ms()->tmp = tmp2, 0);
	return (1);
}

int	ft_check_subs(t_token *token, int min_prec)
{
	int		count;
	t_token	*tmp;
	t_token	*tmp2;

	if (min_prec > 0)
		return (1);
	count = 1;
	tmp2 = token->prev;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_SUBSHELL_OPEN)
			count++;
		else if (tmp->type == TOKEN_SUBSHELL_CLOSE)
		{
			count--;
			if (count < 0)
				return (ft_set_parse_err(E_SYNTAX), get_ms()->tmp = tmp, 0);
		}
		tmp = tmp->next;
	}
	if (count != 0)
		return (ft_set_parse_err(E_SYNTAX), get_ms()->tmp = tmp2, 0);
	return (1);
}
