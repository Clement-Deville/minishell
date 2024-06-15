/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:15:30 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/15 16:07:55 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <minishell.h>

void	ft_add_token_else(char **line, t_token **t_list)
{
	t_token	*token;
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = *line;
	while (tmp[i] && !ft_is_char(tmp + i))
		i++;
	value = malloc(sizeof(char) * (i + 1));
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

int	ft_token_else_by_quotes(char **line, t_token **t_list)
{
	int		i;
	char	quote_type;

	if (*line && (**line == '"' || **line == '\''))
	{
		quote_type = **line; // Sauvegarder le type de guillemet
		i = 1; // Initialiser l'index à 1 pour sauter le guillemet initial
		while ((*line)[i] && (*line)[i] != quote_type) // Boucle jusqu'à trouver le guillemet fermant
			i++;
		if (!(*line)[i] && (*line)[i - 1] != quote_type) // Si guillemet fermant non trouvé
		{
			ft_set_parse_err(quote_type == '"' ? E_DQUOTES : E_QUOTES);
			return (0);
		}
		// Ajouter le token incluant les guillemets
		ft_add_token_sign(line, t_list, TOKEN_ELSE, i + 1);
		*line += i + 1; // Avancer le pointeur de ligne
	}
	return (1);
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
		else if (!ft_strncmp(line, "\"", 1) || ! ft_strncmp(line, "'", 1))
		{
			if (!ft_token_else_by_quotes(&line, &token_list))
				return (free(trimmed), ft_clear_token(token_list), (0));
		}
		else if (is_space(*line))
			line++;
		else
			ft_add_token_else(&line, &token_list);
	}
	ms->tokens = token_list;
	return (free(trimmed), 1);
}
