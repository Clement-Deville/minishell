/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:37 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 17:13:45 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	sub_in_sub_error(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = token->prev;
	while (tmp)
	{
		if (tmp->type == TOKEN_SUBSHELL_OPEN
			&& tmp->next->type == TOKEN_SUBSHELL_OPEN)
		{
			tmp2 = tmp;
			while (tmp)
			{
				if (tmp->type == TOKEN_SUBSHELL_CLOSE
					&& tmp->next->type == TOKEN_SUBSHELL_CLOSE)
					return (ft_set_parse_err(E_SYNTAX),
						get_ms()->tmp = tmp2, 0);
				else if (tmp->type == TOKEN_SUBSHELL_CLOSE
					&& tmp->next->type != TOKEN_SUBSHELL_CLOSE)
					break ;
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
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
