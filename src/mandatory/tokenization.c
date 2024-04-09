/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:24:02 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/09 23:27:02 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_add_token_else(char **line, t_token **t_list)
{
	t_token	*token;
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = *line;
	if (tmp[i] == '\'' || tmp[i] == '"')
		i = there_is_quotes(tmp);
	else
	{
		while (tmp[i] && !ft_is_char(tmp + i))
			i++;
	}
	value = malloc(sizeof(char) * i + 1);
	if (!value)
		return ;
	ft_strlcpy(value, tmp, i + 1);
	token = create_new_token(value, TOKEN_ELSE);
	if (!token)
	{
		free(value);
		return ;
	}
	lst_token_add_back(t_list, token);
	*line += i;
}

int	ft_add_token_sign(char **line, t_token **t_list,
	t_token_type type, int i)
{
	t_token	*token;
	char	*value;

	value = malloc(sizeof(char) * i + 1);
	if (!value)
		return (0);
	ft_strlcpy(value, *line, i + 1);
	token = create_new_token(value, type);
	if (!token)
	{
		free(value);
		return (0);
	}
	lst_token_add_back(t_list, token);
	return (i);
}

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
	else if (!ft_strncmp(*line, "|", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_PIPE, 1);
	else if (!ft_strncmp(*line, "&&", 2))
		i = ft_add_token_sign(line, t_list, TOKEN_AND, 2);
	else if (!ft_strncmp(*line, "||", 2))
		i = ft_add_token_sign(line, t_list, TOKEN_OR, 2);
	else if (!ft_strncmp(*line, "$", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_VAR_ENV, 1);
	else if (!ft_strncmp(*line, "(", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_SUBSHELL_OPEN, 1);
	else if (!ft_strncmp(*line, ")", 1))
		i = ft_add_token_sign(line, t_list, TOKEN_SUBSHELL_CLOSE, 1);
	*line += i;
}

void	ft_tokenization(t_mini_env *ms)
{
	t_token	*token_list;
	char	*line;

	line = ms->line;
	token_list = NULL;
	while (*line)
	{
		if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1)
			|| !ft_strncmp(line, "$", 1))
			ft_token_identify(&line, &token_list);
		else if (!ft_strncmp(line, "\"", 1) || !ft_strncmp(line, "'", 1))
			ft_add_token_else(&line, &token_list);
		else if (is_space(*line))
			line++;
		else
			ft_add_token_else(&line, &token_list);
	}
	ms->tokens = token_list;
}
