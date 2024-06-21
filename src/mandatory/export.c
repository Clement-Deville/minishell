/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:15:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 11:44:57 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	change_value(char *argument, t_dblist *env, t_bool silent)
{
	char	*name;

	name = get_name(argument);
	if (name == NULL)
	{
		if (!silent)
			perror("Malloc error");
		return (-1);
	}
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

int	add_new_variable(char *argument, t_dblist **env, t_bool silent)
{
	t_dblist	*new;
	t_variable	*variable;

	variable = create_variable(argument);
	if (is_valid_name(variable->name) == FALSE)
	{
		if (silent == FALSE)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(variable->name, 2);
			ft_putstr_fd("\": not a valid identifier\n", 2);
		}
		free(variable->name);
		variable->name = NULL;
		free(variable->value);
		variable->value = NULL;
		free(variable);
		return (1);
	}
	new = ft_dblstnew(variable);
	if (new == NULL || new->content == NULL)
		return (free(new), -1);
	ft_dblstadd_back(env, new);
	return (0);
}

int	export_one(char *argument, t_dblist **env, t_bool silent)
{
	char	*name;

	name = get_name(argument);
	if (name == NULL)
	{
		if (!silent)
			perror("Malloc error");
		return (-1);
	}
	if (name_exists(name, *env) == TRUE)
	{
		free(name);
		if (change_value(argument, *env, silent) == -1)
			return (-1);
		return (0);
	}
	else
	{
		free(name);
		return (add_new_variable(argument, env, silent));
	}
}

int	do_export(t_node *node, t_dblist **env)
{
	int		i;
	char	**arguments;
	int		status;
	int		exit_status;

	i = 0;
	exit_status = 0;
	arguments = &(node->c_cmd->expand)[1];
	if (arguments[0] == NULL && node->silent == FALSE)
		return (print_export(*env), 0);
	while (arguments[i])
	{
		status = export_one(arguments[i], env, node->silent);
		if (status == -1)
			return (1);
		if (status)
			exit_status = status;
		i++;
	}
	return (exit_status);
}
