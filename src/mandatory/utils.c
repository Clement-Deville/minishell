/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:59:15 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/10 14:22:44 by cdeville         ###   ########.fr       */
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
			ft_strlen(argument)) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

void	print_variable_export(void *content)
{
	ft_putstr_fd(((t_variable *)content)->name, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(((t_variable *)content)->value, 1);
	ft_putstr_fd("\"\n", 1);
}
