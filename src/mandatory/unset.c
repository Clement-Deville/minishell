/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:16:32 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/10 17:20:23 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_element(t_dblist *env)
{
	if (env->prev)
		env->prev->next = env->next;
	if (env->next)
		env->next->prev = env->prev;
	destroy_variable(env->content);
	free(env);
}

int	delete_variable(char *argument, t_dblist *env)
{
	char	*name;

	name = get_name(argument);
	if (name == NULL)
		return (perror("Malloc error"), -1);
	while (env)
	{
		if (ft_strncmp(name, (((t_variable *)(env->content))->name),
			ft_strlen(name)) == 0)
			break ;
		env = env->next;
	}
	remove_element(env);
	return (free(name), 0);
}

int	unset_one(char *argument, t_dblist *env)
{
	char	*name;

	name = get_name(argument);
	if (name == NULL)
		return (perror("Malloc error"), -1);
	if (name_exists(name, env) == TRUE)
	{
		delete_variable(argument, env);
		return (free(name), 0);
	}
	else
		return (free(name), -1);
}

int	do_unset(char **arguments, t_dblist *env)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		if (unset_one(arguments[i], env) == -1)
			return (1);
		i++;
	}
	return (0);
}
