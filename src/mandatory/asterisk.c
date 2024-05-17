/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:46:35 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/07 15:42:00 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	pass_wilcard(char **ptr_on_argument, char **ptr_on_d_name)
{
	while (**ptr_on_argument == '*')
		(*ptr_on_argument)++;
	if (!**ptr_on_argument)
		return (TRUE);
	while (**ptr_on_d_name && **ptr_on_d_name != **ptr_on_argument)
		(*ptr_on_d_name)++;
	return (FALSE);
}

static char	*pass_matching(char **ptr_on_argument, char **ptr_on_d_name)
{
	char	*last_char;

	last_char = (*ptr_on_d_name) + 1;
	while (**ptr_on_argument && **ptr_on_argument == **ptr_on_d_name)
	{
		(*ptr_on_argument)++;
		(*ptr_on_d_name)++;
	}
	return (last_char);
}

t_bool	patern_match(char *argument, char *d_name)
{
	char	*last_wildcard;
	char	*last_char;

	last_char = NULL;
	last_wildcard = NULL;
	if (argument == NULL || d_name == NULL || *d_name == 0)
		return (FALSE);
	while (*argument)
	{
		if (*argument == '*')
		{
			last_wildcard = argument;
			if (pass_wilcard(&argument, &d_name) == TRUE)
				return (TRUE);
		}
		else if (*argument == *d_name)
			last_char = pass_matching(&argument, &d_name);
		else if (d_name == 0)
			return (FALSE);
		else
			return (patern_match(last_wildcard, last_char));
	}
	if (*argument == 0 && *d_name == 0)
		return (TRUE);
	return (patern_match(last_wildcard, last_char));
}

int	do_asterisk(char *argument)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	dir = do_opendir();
	if (dir == NULL)
		return (2);
	entry = readdir(dir);
	i = 0;
	while (entry != NULL)
	{
		if (patern_match(argument, entry->d_name) == TRUE)
			i++;
		// else
		// 	ft_printf("Not matching: %s\n", entry->d_name);
		entry = readdir(dir);
	}
	if (do_closedir(dir) != 0)
		return (2);
	return (i);
}
