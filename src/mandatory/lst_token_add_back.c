/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_addback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:53:24 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/09 09:59:09 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token *last_token(t_token *token)
{
    if (!token)
        return (NULL);
    while (token->next)
        token = token->next;
    return (token);
}

void    lst_token_add_back(t_token **token_list, t_token *new)
{
    t_token *last;

    if (!new)
        return ;
    if (token_list)
    {
        if (!*token_list)
            *token_list = new;
        else
        {
            last = last_token(*token_list);
            last->next = new;
            new->prev = last;
        }

    }
}