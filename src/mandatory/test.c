/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:24:02 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/09 10:49:26 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    ft_token_identify(char **line, t_token **t_list, t_mini_env *ms)
{
    if (!ft_strncmp(*line, ">>", 2))
        ft_printf("<<");
    else if (!ft_strncmp(*line, "<<", 2))
        ft_printf("<<");
}

t_token create_new_token(char *value, t_token_type type)
{
    t_token *new;

    new = (t_token *)ft_calloc(1, siweof(t_token));
    if (!new)
        return (NULL);
    new->value = value;
    new->type = type;
    return (new);
}

void    ft_add_token_else(char **line, t_token **t_list, t_mini_env *ms)
{
    t_token_type	type;
    char			*value;
    int             i;


	lst_token_add_back()
    *line += i;
}

void ft_tokenization(t_mini_env *ms)
{
    t_token *token_list;
    char    *line;

    line = *(ms->line);
    token_list =NULL;
    while (*line)
    {
        if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
            || !ft_strncmp(line, "|", 1) || !ftstrncmp(line, "&&", 2)
            || !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1)
            || !ft_strncmp(line, "$", 1))
            ft_token_identify(&line, &token_list, ms);
        else
            ft_add_token_else(&line, &token_list, ms);
    }
}