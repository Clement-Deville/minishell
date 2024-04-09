/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:15:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 19:02:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	no_value(char *argument)
{
	if (ft_strchr(argument, '=') == NULL)
		return (TRUE);
	return (FALSE);
}

t_bool	name_exists(char *argument, t_dblist *env)
{
	while (env)
	{
		if (ft_strncmp(argument, (((t_variable *)(env->content))->name),
			ft_strlen(argument)) == 0
			&& (((t_variable *)(env->content))->name)[ft_strlen(argument)] == '=')
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

int	change_value(char *argument, t_dblist *env)
{
	while (env)
	{
		if (ft_strncmp(argument, (((t_variable *)(env->content))->name),
			ft_strlen(argument)) == 0
			&& (((t_variable *)(env->content))->name)[ft_strlen(argument)] == '=')
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
	if (no_value(argument) == TRUE)
		return (0);
	else if (name_exists(argument, env) == TRUE)
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

static t_bool	is_smaller(t_variable *actual, t_variable *min)
{
	if (min == NULL)
		return (TRUE);
	if (ft_strncmp(actual->name, min->name, ft_strlen(min->name) + 1) < 0)
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	is_bigger(t_variable *actual, t_variable *prev_min)
{
	if (prev_min == NULL)
		return (TRUE);
	if (ft_strncmp(actual->name, prev_min->name,
			ft_strlen(prev_min->name) + 1) > 0)
		return (TRUE);
	else
		return (FALSE);
}

t_variable	*get_first_min(t_dblist *env)
{
	t_variable	*min;
	t_dblist	*actual;

	actual = env;
	min = NULL;
	while (actual)
	{
		if (is_smaller((t_variable *)(actual->content), min))
			min = (t_variable *)(actual->content);
		actual = actual->next;
	}
	return (min);
}

t_variable	*get_biggest(t_dblist *env)
{
	t_variable	*max;
	t_dblist	*actual;

	actual = env;
	max = NULL;
	while (actual)
	{
		if (is_bigger((t_variable *)(actual->content), max))
			max = (t_variable *)(actual->content);
		actual = actual->next;
	}
	return (max);
}

t_variable	*get_new_min(t_variable *prev_min, t_dblist *env)
{
	t_variable	*min;
	t_dblist	*actual;

	actual = env;
	min = get_biggest(env);
	while (actual)
	{
		if (is_smaller((t_variable *)(actual->content), min)
			&& is_bigger((t_variable *)(actual->content), prev_min))
		{
			min = (t_variable *)(actual->content);
		}
		actual = actual->next;
	}
	return (min);
}

void	print_export(t_dblist *env)
{
	t_variable	*prev_min;
	t_variable	*new_min;

	prev_min = NULL;
	while (1)
	{
		new_min = get_new_min(prev_min, env);
		if (new_min == prev_min)
			break ;
		print_variable(new_min);
		prev_min = new_min;
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
		export_one(arguments[i], env);
		i++;
	}
	return (0);
}
