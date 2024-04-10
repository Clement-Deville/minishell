/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:15:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/10 13:01:41 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	change_value(char *argument, t_dblist *env)
{
	while (env)
	{
		if (ft_strncmp(argument, (((t_variable *)(env->content))->name),
			ft_strlen(argument)) == 0
			&& (((t_variable *)(env->content))->name)[ft_strlen(argument)]
				== '=')
			break ;
		env = env->next;
	}
	destroy_variable(env->content);
	env->content = create_variable(argument);
	if (env->content == NULL)
		return (-1);
	return (0);
}

int	add_new_variable(char *argument, t_dblist *env)
{
	t_dblist	*new;

	new = ft_dblstnew(create_variable(argument));
	if (new == NULL || new->content == NULL)
		return (free(new), -1);
	ft_dblstadd_back(&env, new);
	return (0);
}

int	export_one(char *argument, t_dblist *env)
{
	if (name_exists(argument, env) == TRUE)
	{
		if (change_value(argument, env) == -1)
			return (1);
		return (0);
	}
	else
	{
		if (add_new_variable(argument, env) == -1)
			return (-1);
		return (0);
	}
}

int	do_export(char **arguments, t_dblist *env)
{
	int	i;

	i = 0;
	if (arguments == NULL)
		return (print_export(env), 0);
	while (arguments[i])
	{
		if (export_one(arguments[i], env) == -1)
			return (-1);
		i++;
	}
	return (0);
}
