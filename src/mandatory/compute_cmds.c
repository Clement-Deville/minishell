/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:44:53 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/28 15:13:44 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_node(t_node *node)
{
	node->c_cmd = ft_calloc(1, sizeof(t_compute_cmd));
	if (!node->c_cmd)
		return (0);
	node->c_cmd->ac = 0;
	node->c_cmd->av = NULL;
	node->c_cmd->wildcard = ft_calloc(1, sizeof(t_wildcard));
	if (!node->c_cmd->wildcard)
		return (0);
	node->c_cmd->expand = NULL;
	node->c_cmd->redir = NULL;
	return (1);
}

char	*ft_handle_arg(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dq_arg(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

int	ft_is_valid_arg(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_str_find_env(char *arg)
{
	t_mini_env	*ms;

	ms = get_ms();
	while (ms->envlst)
	{
		if (!ft_strncmp(arg, ((t_variable *)ms->envlst->content)->name,
				ft_strlen(arg)))
			return (((t_variable *)ms->envlst->content)->value);
		ms->envlst = ms->envlst->next;
	}
	return (NULL);
}

char	*ft_handle_dollar(char *str, int *i)
{
	int			start;
	char		*arg;
	char		*env;

	*i += 1;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		*i += 1;
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		*i += 1;
		return (ft_itoa(get_ms()->exit));
	}
	else if (!ft_is_valid_arg(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && ft_is_valid_arg(str[*i]))
		*i += 1;
	arg = ft_substr(str, start, *i - start);
	env = ft_str_find_env(arg);
	if (!env)
		return (free(arg), ft_strdup(""));
	return (free(arg), ft_strdup(env));
}

char	*ft_handle_simple_quotes(char *str, int *i)
{
	int	start;

	start = *i;
	*i += 1;
	while (str[*i] && str[*i] != '\'')
		*i += 1;
	*i += 1;
	return (ft_substr(str, start, *i - start));
}

char *ft_handle_double_quotes(char *str, int *i)
{
	char	*new;

	new = ft_strdup("\"");
	if (!new)
		return (NULL);
	*i += 1;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			new = ft_strjoin(new, ft_handle_dollar(str, i));
			if (!new)
				return (NULL);
		}
		else
		{
			new = ft_strjoin(new, ft_handle_dq_arg(str, i));
			if (!new)
				return (NULL);
		}
	}
	*i += 1;
	return (ft_strjoin(new, "\""));
}

int		check_quotes(char *str)
{
	int	i;
	int	count;
	int	count2;

	i = 0;
	count = 0;
	count2 = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			count++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
			{
				count++;
				i++;
			}
		}
		else if (str[i] == '"')
		{
			i++;
			count2++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '"')
			{
				count2++;
				i++;
			}
		}
		else
			i++;
	}
	return ((count + count2) % 2);
}

char	*ft_cmd_pre_expand(char *str)
{
	char	*new;
	char	*tmp;
	char	*temp;
	int		i;

	i = 0;
	if (check_quotes(str))
		return (ft_printf("PB QUOTES NOT CLOSED --> TO FREE"), NULL);
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			temp = ft_handle_simple_quotes(str, &i);
		else if (str[i] == '"')
			temp = ft_handle_double_quotes(str, &i);
		else if (str[i] == '$')
			temp = ft_handle_dollar(str, &i);
		else
			temp = ft_handle_arg(str, &i);
		if (!temp)
			return (free(tmp), NULL);
		new = ft_strjoin(tmp, temp);
		free(temp);
		free(tmp);
		if (!new)
			return (NULL);
		tmp = new;
	}
	return (tmp);
}

char	*skip_words(char *str, int *i, int *count, char *tmp)
{
	int	start;

	start = *i;
	if (*count == 0)
	{
		while (str[start] && str[start] != ' ')
			start++;
		tmp = ft_calloc(start - *i + 1, sizeof(char));
		if (!tmp)
			return (NULL);
	}
	while (str[*i] && str[*i] != ' ')
	{
		tmp[*count] = str[*i];
		*count += 1;
		*i += 1;
	}
	if (str[*i] != '\0')
		*i += 1;
	tmp[*count] = '\0';
	return (tmp);
}

int		find_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int		is_quotes(char c, char x)
{
	if (c == x)
		return (1);
	return (0);
}

char	assign_quote(char c)
{
	char	quote;

	if (c == '\'')
		quote = '\'';
	else
		quote = '"';
	return (quote);
}

char	*skip_quotes(char *str, int *i, int *count, char *tmp)
{
	int		start;
	char	quote;

	quote = assign_quote(str[*i]);
	*i += 1;
	start = *i;
	if (*count == 0)
	{
		while (str[start] && !is_quotes(str[start], quote))
			start++;
		tmp = ft_calloc(start + 1 + 2, sizeof(char));
		if (!tmp)
			return (NULL);
	}
	tmp[*count] = '"';
	*count += 1;
	while (str[*i] && !is_quotes(str[*i], quote))
	{
		tmp[*count] = str[*i];
		*count += 1;
		*i += 1;
	}
	if (str[*i] != '\0' && str[*i] != ' ')
		tmp = skip_words(str, i, count, tmp);
	else if (str[*i] != '\0' && str[*i == ' '])
		*i += 1;
	tmp[*count] = '\0';
	return (tmp);
}

int	countwords(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (s[0] != c && s[0])
		words++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			words++;
		i++;
	}
	return (words);
}

char	**ft_split_args(char *str, t_node *node)
{
	char	**tmp;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	node->c_cmd->ac = countwords(str, ' ');
	tmp = ft_calloc(countwords(str, ' ') + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		count = 0;
		if (str[i] && str[i] != ' ' && !find_quotes(str[i]))
			tmp[j] = skip_words(str, &i, &count, tmp[j]);
		else if (str[i] && str[i] != ' ' && find_quotes(str[i]))
			tmp[j] = skip_quotes(str, &i, &count, tmp[j]);
		if (tmp[j] == NULL)
		{
			while (j > 0)
				free(tmp[--j]);
			free(tmp);
			return (NULL);
		}
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char	**no_asterisk(char *str)
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(str);
	if (!ret[0])
		return (NULL);
	return (ret);
}

int	ft_visible(char *entry)
{
	if (entry[0] == '.')
		return (0);
	return (1);
}

char	**there_asterisk(char *str, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**ret;

	dir = do_opendir();
	ret = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (patern_match(str, entry->d_name) && ft_visible(entry->d_name))
		{
			ret[i] = ft_strdup(entry->d_name);
			if (!ret[i])
				return (NULL);
			i++;
		}
		entry = readdir(dir);
	}
	do_closedir(dir);
	return (ret);
}

char	**ft_expand_wildcard(char *str, t_node *node)
{
	int				i;
	char			**ret;

	i = do_asterisk(str);
	node->c_cmd->ac += i;
	if (!ft_contains_asterisk(str) || !i)
	{
		ret = no_asterisk(str);
		if (!ret)
			return (NULL);
	}
	else
	{
		ret = there_asterisk(str, i);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

char	**ft_join_wildcard(t_node *node)
{
	int			j;
	int			k;
	char		**joined;
	t_wildcard	*wildcard;


	joined = ft_calloc(node->c_cmd->ac + 2, sizeof(char *));
	if (!joined)
		return (NULL);
	k = 0;
	wildcard = node->c_cmd->wildcard;
	while (wildcard->next != NULL)
	{
		j = 0;
		while (wildcard->files[j])
		{
			joined[k] = ft_strdup(wildcard->files[j]);
			j++;
			k++;
		}
		wildcard = wildcard->next;
	}
	joined[k] = NULL;
	return (joined);
}

void	ft_big_free(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
void	free_wildcards(t_wildcard *wildcard)
{
	t_wildcard	*temp;
	int			i;

	while (wildcard != NULL)
	{
		temp = wildcard;
		wildcard = wildcard->next;
		if (temp->files != NULL)
		{
			i = 0;
			while (temp->files[i] != NULL)
			{
				free(temp->files[i]);
				i++;
			}
			free(temp->files);
		}
		free(temp);
	}
}

char	**ft_handle_wildcard(char **glob, t_node *node)
{
	int 		i;
	char		**new;
	t_wildcard	*wildcard;

	i = 0;
	wildcard = node->c_cmd->wildcard;
	while (glob[i])
	{
		wildcard->next = ft_calloc(1, sizeof(t_wildcard));
		if (!wildcard->next)
			return (NULL);
		wildcard->files = ft_expand_wildcard(glob[i], node);
		if (!wildcard->files)
			return (NULL);
		wildcard = wildcard->next;
		i++;
	}
	wildcard->next = NULL;
	new = ft_join_wildcard(node);
	return (ft_big_free(glob), free_wildcards(node->c_cmd->wildcard), new);
}

char	*clean_node(char *str)
{
	int		i;
	int		j;
	int		dstsize;
	char	*tmp;
	char	*ret;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2])
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
			i += 2;
		else
			tmp[j++] = str[i++];
	}
	free(str);
	dstsize = ft_strlen(tmp) + 1;
	ret = ft_calloc(dstsize, sizeof(char));
	return (ft_strlcpy(ret, tmp, dstsize), free(tmp), ret);
}

char	**ft_expand(char *str, t_node *node)
{
	char	**global;
	char	*expanded;

	expanded = NULL;
	expanded = ft_cmd_pre_expand(str);
	if (!expanded)
		return (NULL);
	expanded = clean_node(expanded);
	if (!expanded)
		return (NULL);
	global = ft_split_args(expanded, node);
	free(expanded);
	if (!global)
		return (NULL);
	return (global);
}

void	cut_quotes(char **str)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = -1;
	while (str[++i] != NULL)
	{
		j = -1;
		k = 0;
		new = ft_calloc(ft_strlen(str[i]) + 1, sizeof(char));
		if (!new)
			return ;
		while (str[i][++j] != '\0')
		{
			if (str[i][j] == '"')
				j++;
			if (str[i][j] == '\0')
				break ;
			new[k] = str[i][j];
			k++;
		}
		new[k] = '\0';
		free(str[i]);
		str[i] = new;
	}
}

void free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->c_cmd)
	{
		if (node->c_cmd->av)
			ft_big_free(node->c_cmd->av);
		if (node->c_cmd->expand)
			ft_big_free(node->c_cmd->expand);
		if (node->c_cmd->wildcard)
			free(node->c_cmd->wildcard);
		free(node->c_cmd);
	}
	free(node);
}

void	init_cmp(t_node *node)
{
	char **tmp;

	tmp = NULL;
	if (!init_node(node))
	{
		free_node(node);
		return ;
	}
	if (node->cmd != NULL)
		tmp = ft_expand(node->cmd, node);
	if (!tmp)
		return ;
	node->c_cmd->expand = ft_handle_wildcard(tmp, node);
	if (!node->c_cmd->expand)
	{
		free_node(node);
		return ;
	}
	cut_quotes(node->c_cmd->expand);
}

void	ft_compute_cmds(t_node *node)
{
	if (node == NULL || (node->cmd == NULL && node->sub_node == NULL
			&& node->red_node == NULL))
		return ;
	else if (node->sub_node != NULL)
	{
		if (node->next && node->next->red_node != NULL)
		{
			node = node->next;
			ft_init_heredoc(node);
			init_node(node);
			ft_compute_cmds(node->next);
		}
		else
			ft_compute_cmds(node->next);
		return ;
	}
	else if (node->red_node != NULL)
		ft_init_heredoc(node);
	init_cmp(node);
	ft_compute_cmds(node->next);
}
