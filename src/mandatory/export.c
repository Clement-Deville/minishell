/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:15:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/31 18:37:02 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	add_new_variable(char *argument, t_dblist **env)
{
	t_dblist	*new;

	// Pas besoin de double pointeur, a verfier
	new = ft_dblstnew(create_variable(argument));
	// ft_printf("New argument value = %s\n", ((t_variable*)(new->content))->value);
	if (new == NULL || new->content == NULL)
		return (free(new), -1);
	// ft_printf("Adding new value\n");
	ft_dblstadd_back(env, new);
	// t_dblist	*test;
	// test = ft_dblstlast(*env);
	// ft_printf("Last argument value = %s\n", ((t_variable*)(test->content))->value);
	// print_variable(test->content);
	// ft_printf("Last argument next : %p\n", test->next);
	// ft_printf("Last argument prev:");
	// print_variable(test->prev->content);
	return (0);
}

int	export_one(char *argument, t_dblist **env)
{
	char	*name;

	name = get_name(argument);
	if (name == NULL)
		return (perror("Malloc error"), -1);
	if (name_exists(name, *env) == TRUE)
	{
		free(name);
		if (change_value(argument, *env) == -1)
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

int	do_export(t_node *node, t_dblist **env)
{
	int		i;
	char	**arguments;

	i = 0;
	arguments = &(node->c_cmd->expand)[1];
	if (arguments[0] == NULL && node->silent == FALSE)
		return (print_export(*env), 0);
	while (arguments[i])
	{
		if (export_one(arguments[i], env) == -1)
			return (1);
		i++;
	}
	return (0);
}
