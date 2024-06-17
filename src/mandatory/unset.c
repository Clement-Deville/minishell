/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:16:32 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/17 16:18:15 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_element(t_dblist *element)
{
	if (element->prev)
		element->prev->next = element->next;
	if (element->next)
		element->next->prev = element->prev;
	destroy_variable(element->content);
	free(element);
}

int	delete_variable(char *argument, t_dblist **env)
{
	char		*name;
	t_dblist	*actual;

	actual = *env;
	name = get_name(argument);
	if (name == NULL)
		return (perror("Malloc error"), -1);
	while (actual)
	{
		if (ft_strncmp(name, (((t_variable *)(actual->content))->name),
			ft_strlen(name)) == 0)
			break ;
		actual = actual->next;
	}
	if (actual == *env)
		*env = (*env)->next;
	remove_element(actual);
	return (free(name), 0);
}

int	unset_one(char *argument, t_dblist **env)
{
	char	*name;

	name = get_name(argument);
	if (name == NULL)
		return (perror("Malloc error"), -1);
	if (name_exists(name, *env) == TRUE)
	{
		if (delete_variable(argument, env))
			return (free(name), -1);
		return (free(name), 0);
	}
	else
		return (free(name), 1);
}

int	do_unset(char **arguments, t_dblist **env)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 0;
	i = 0;
	while (arguments[i])
	{
		status = unset_one(arguments[i], env);
		if (status == -1)
			return (1);
		if (status)
			exit_status = status;
		i++;
	}
	return (exit_status);
}
