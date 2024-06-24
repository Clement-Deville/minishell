/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:15:30 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 14:42:00 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_quote_err(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	get_ms()->f_or_nf = 0;
	get_ms()->exit = 258;
}

int	ft_add_token_else(char **line, t_token **t_list)
{
	char	*tmp;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp = *line;
	i = 0;
	while (tmp[i] && !ft_is_char(tmp + i))
	{
		if (ft_is_quote(tmp[i]))
		{
			if (!ft_skip_quotes(tmp, &i))
				return (ft_print_quote_err(tmp[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp, 0, i);
	if (!value)
		return (0);
	token = create_new_token(value, TOKEN_ELSE);
	if (!token)
		return (free(value), 0);
	*line += i;
	return (lst_token_add_back(t_list, token), 1);
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

int	ft_tokenization(t_mini_env *ms)
{
	t_token	*token_list;
	char	*line;
	char	*trimmed;

	line = ft_strtrim(ms->line, " \f\n\r\t\v");
	if (!line)
		return (1);
	token_list = NULL;
	trimmed = line;
	while (*line)
	{
		if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
			ft_token_identify(&line, &token_list);
		else if (is_space(*line))
			line++;
		else
		{
			if (!ft_add_token_else(&line, &token_list))
				return (free(trimmed), (0));
		}
	}
	ms->tokens = token_list;
	return (free(trimmed), 1);
}
