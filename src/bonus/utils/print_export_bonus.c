/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:05:13 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/10 12:48:54 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		print_variable_export(new_min);
		prev_min = new_min;
	}
}
