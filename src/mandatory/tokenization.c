/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:15:30 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/20 12:04:40 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ft_is_separator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (1);
	return (0);
}

t_bool	ft_skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

void	ft_print_quote_err(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	get_ms()->f_or_nf = 1;
	get_ms()->exit = 258;
}

int	ft_add_token_else(char **line_ptr, t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !ft_is_separator(tmp_line + i))
	{
		if (ft_is_quote(tmp_line[i]))
		{
			if (!ft_skip_quotes(tmp_line, &i))
				return (ft_print_quote_err(tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = create_new_token(value, TOKEN_ELSE);
	if (!token)
		return (free(value), 0);
	*line_ptr += i;
	return (lst_token_add_back(token_list, token), 1);
}

// void	ft_add_token_else(char **line, t_token **t_list)
// {
// 	t_token	*token;
// 	char	*value;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = *line;
// 	// Ajout d'une condition pour vérifier les caractères spéciaux pertinents
// 	while (tmp[i] && !is_space(tmp[i]) && tmp[i] != '"' && tmp[i] != '\'' && tmp[i] != '|' && tmp[i] != '<' && tmp[i] != '>' && tmp[i] != '&' && tmp[i] != '(' && tmp[i] != ')')
// 		i++;
// 	value = malloc(sizeof(char) * (i + 1));
// 	if (!value)
// 		return ;
// 	ft_strlcpy(value, tmp, i + 1);
// 	token = create_new_token(value, TOKEN_ELSE);
// 	if (!token)
// 	{
// 		free(value);
// 		return ;
// 	}
// 	lst_token_add_back(t_list, token);
// 	*line += i;
// }

// void	ft_add_token_else(char **line, t_token **t_list)
// {
// 	t_token	*token;
// 	char	*value;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = *line;
// 	while (tmp[i] && !ft_is_char(tmp + i))
// 		i++;
// 	value = malloc(sizeof(char) * (i + 1));
// 	if (!value)
// 		return ;
// 	ft_strlcpy(value, tmp, i + 1);
// 	token = create_new_token(value, TOKEN_ELSE);
// 	if (!token)
// 	{
// 		free(value);
// 		return ;
// 	}
// 	lst_token_add_back(t_list, token);
// 	*line += i;
// }

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

int	in_quotes(char **tmp, char **line)
{
	char	quote_type;
	int		i;

	if (*line && (**line == '"' || **line == '\''))
	{
		quote_type = **line;
		i = 1;
		while ((*line)[i])
		{
			if ((*line)[i] == quote_type)
				break ;
			else
				i++;
		}
		if (!(*line)[i] && (*line)[i - 1] != quote_type)
		{
			ft_set_parse_err(quote_type == '"' ? E_DQUOTES : E_QUOTES);
			return (0);
		}
		if (!tmp)
		{
			tmp = malloc(sizeof(char) * i + 1);
			if (!tmp)
				return (0);
		}
		ft_strlcpy(*tmp, *line, i + 2);
		*line += i + 3;
	}
	return (1);
}

// int	ft_token_else_by_quotes(char **line, t_token **t_list)
// {
// 	int		i;
// 	t_token	*token;
// 	char	quote_type;
// 	char	*tmp;

// 	if (*line && (**line == '"' || **line == '\''))
// 	{
// 		quote_type = **line;
// 		i = 0;
// 		while ((*line)[i])
// 		{
// 			if ((*line)[i] == quote_type)
// 				in_quotes(&tmp, line);
// 			if (!**line || (**line) == ' ')
// 				break ;
// 			else
// 			{
// 				if (!tmp)
// 				{
// 					tmp = malloc(sizeof(char) * i + 1);
// 					if (!tmp)
// 						return (0);
// 				}
// 				ft_strlcpy(tmp, *line, i + 1);
// 			}
// 			i++;
// 		}
// 		token = create_new_token(tmp, TOKEN_ELSE);
// 		if (!token)
// 		{
// 			free(tmp);
// 			return (0);
// 		}
// 		lst_token_add_back(t_list, token);
// 		*line += i + 1;
// 	}
// 	return (1);
// }

int	ft_token_else_by_quotes(char **line, t_token **t_list)
{
	int		i;
	t_token	*token;
	char	quote_type;
	char	*tmp = NULL;

	if (*line && (**line == '"' || **line == '\''))
	{
		quote_type = **line;
		i = 1;
		while ((*line)[i])
		{
			if ((*line)[i] == quote_type)
			{
				i++;
				break;
			}
			i++;
		}
		if (!(*line)[i - 1])
		{
			ft_set_parse_err(quote_type == '"' ? E_DQUOTES : E_QUOTES);
			return (0);
		}
		tmp = malloc(sizeof(char) * (i + 1));
		if (!tmp)
			return (0);
		ft_strlcpy(tmp, *line, i + 1);
		*line += i;

		while (**line && !is_space(**line))
		{
			i = 0;
			while ((*line)[i] && !is_space((*line)[i]) && (*line)[i] != '<' && (*line)[i] != '>' && (*line)[i] != '|' && (*line)[i] != '&' && (*line)[i] != '(' && (*line)[i] != ')')
				i++;
			char *tmp2 = malloc(sizeof(char) * (strlen(tmp) + i + 1));
			if (!tmp2)
			{
				free(tmp);
				return (0);
			}
			ft_strlcpy(tmp2, tmp, strlen(tmp) + 1);
			ft_strlcat(tmp2, *line, strlen(tmp) + i + 1);
			free(tmp);
			tmp = tmp2;
			*line += i;
		}
		token = create_new_token(tmp, TOKEN_ELSE);
		if (!token)
		{
			free(tmp);
			return (0);
		}
		lst_token_add_back(t_list, token);
	}
	return (1);
}


// int	ft_token_else_by_quotes(char **line, t_token **t_list)
// {
// 	int		i;
// 	char	quote_type;

// 	if (*line && (**line == '"' || **line == '\''))
// 	{
// 		quote_type = **line;
// 		i = 1;
// 		while ((*line)[i])
// 		{
// 			if ((*line)[i] == quote_type)
// 				break ;
// 			else
// 				i++;
// 		}
// 		if (!(*line)[i] && (*line)[i - 1] != quote_type)
// 		{
// 			ft_set_parse_err(quote_type == '"' ? E_DQUOTES : E_QUOTES);
// 			return (0);
// 		}
// 		ft_add_token_sign(line, t_list, TOKEN_ELSE, i + 1);
// 		*line += i + 1;
// 	}
// 	return (1);
// }

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
				return (free(trimmed), ft_clear_token(token_list), (0));
		}
	}
	ms->tokens = token_list;
	return (free(trimmed), 1);
}
