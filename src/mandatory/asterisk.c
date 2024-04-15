/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:46:35 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/15 14:53:47 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			while (*argument == '*')
				argument++;
			if (*argument == 0)
				return (TRUE);
			while (*d_name && *d_name != *argument)
				d_name++;
			if (*d_name && *d_name == *argument)
				last_char = d_name + 1;
		}
		else if (*argument == *d_name)
		{
			last_char = d_name + 1;
			while (*argument && *argument == *d_name)
			{
				argument++;
				d_name++;
			}
		}
		else if (d_name == 0)
		{
			return (FALSE);
		}
		else
			return (patern_match(last_wildcard, last_char));
	}
	if (*argument == 0 && *d_name == 0)
		return (TRUE);
	return (patern_match(last_wildcard, last_char));
}

int	do_closedir(DIR *dir)
{
	if (closedir(dir) != 0)
		return (perror("closedir"), 2);
	return (0);
}

DIR	*do_opendir(void)
{
	char	*current_dir_name;
	DIR		*dir;

	current_dir_name = getcwd(NULL, 0);
	if (current_dir_name == NULL)
		return (perror("getcwd error"), NULL);
	dir = opendir(current_dir_name);
	if (dir == NULL)
		perror("Opendir");
	free(current_dir_name);
	return (dir);
}

int	do_asterisk(char *argument)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = do_opendir();
	if (dir == NULL)
		return (2);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (patern_match(argument, entry->d_name) == TRUE)
			ft_printf("Matching: %s\n", entry->d_name);
		else
			ft_printf("Not matching: %s\n", entry->d_name);
		entry = readdir(dir);
	}
	if (do_closedir(dir) != 0)
		return (2);
	return (0);
}
