/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:57:11 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 16:38:42 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_token_identify(char **line, t_token **t_list)
{
	int	i;

	i = 0;
	if (!ft_strncmp(*line, ">>", 2))
		i = ft_add_token_sign(line, t_list, TOKEN_APPEND, 2);
	else if (!ft_strncmp(*line, "<<", 2))
		i = ft_add_token_sign(line, t_list, TOKEN_HERE_DOC, 2);
	else if (!ft_strncmp(*line, "<", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_RED_IN, 1);
	else if (!ft_strncmp(*line, ">", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_RED_OUT, 1);
	else if (!ft_strncmp(*line, "&&", 2))
		i = ft_add_token_sign(line, t_list, TOKEN_AND, 2);
	else if (!ft_strncmp(*line, "||", 2))
		i = ft_add_token_sign(line, t_list, TOKEN_OR, 2);
	else if (!ft_strncmp(*line, "(", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_SUBSHELL_OPEN, 1);
	else if (!ft_strncmp(*line, ")", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_SUBSHELL_CLOSE, 1);
	else
		i = ft_add_token_sign(line, t_list, TOKEN_PIPE, 1);
	*line += i;
}

int	ft_compare_line_token(char *line)
{
	if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
		|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
		|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
		return (0);
	else
		return (1);
}
