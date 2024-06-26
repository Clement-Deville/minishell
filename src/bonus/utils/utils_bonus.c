/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:59:15 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/14 13:05:34 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	nbr_of_args(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (0);
	while (args[i] && args[i + 1])
		i++;
	return (i);
}

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
			ft_strlen(argument) + 1) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

void	print_variable_export(void *content)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(((t_variable *)content)->name, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(((t_variable *)content)->value, 1);
	ft_putstr_fd("\"\n", 1);
}
