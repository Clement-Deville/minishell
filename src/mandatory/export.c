/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:15:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/27 21:03:28 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_variable_valid(char *argument)
{
	int	i;

	i = 0;
	if (ft_isalpha(argument[i++]) == FALSE)
		return (FALSE);
	while (argument[i])
	{
		if ((ft_isalnum(argument[i++]) || argument[i] == '_') == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	change_value(char *argument, t_dblist *env)
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
	destroy_variable(env->content);
	env->content = create_variable(argument);
	if (env->content == NULL)
		return (free(name), -1);
	return (free(name), 0);
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
	char	*name;

	name = get_name(argument);
	if (name == NULL)
		return (perror("Malloc error"), -1);
	if (is_variable_valid(name) == FALSE)
	{
		ft_putstr_fd("export: not an identifer:", 2);
		ft_putstr_fd(name, 2);
		return (ft_putstr_fd("\n", 2), 2);
	}
	if (name_exists(name, env) == TRUE)
	{
		free(name);
		if (change_value(argument, env) == -1)
			return (1);
		return (0);
	}
	else
	{
		free(name);
		if (add_new_variable(argument, env) == -1)
			return (-1);
		return (0);
	}
}

int	do_export(char **arguments, t_dblist *env)
{
	int	i;
	int	ret;
	int exit_value;

	i = 0;
	exit_value = 0;
	if (arguments == NULL)
		return (print_export(env), 0);
	while (arguments[i])
	{
		ret = export_one(arguments[i], env);
		if (ret == -1)
			return (1);
		else if (ret == 2)
			exit_value = 1;
		i++;
	}
	return (exit_value);
}
