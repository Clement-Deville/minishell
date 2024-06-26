/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:53:24 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/17 15:34:54 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	lst_token_add_back(t_token **token_list, t_token *new)
{
	t_token	*curr;

	if (!*token_list)
	{
		*token_list = new;
		return ;
	}
	curr = *token_list;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}
