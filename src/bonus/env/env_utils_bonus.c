/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:30:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 11:31:20 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_valid_name(char *name)
{
	int	i;

	i = 0;
	if (!name || (isalpha(name[0]) == FALSE && name[0] != '_'))
		return (FALSE);
	while (name[++i])
	{
		if (isalnum(name[i]) == FALSE && name[i] != '_')
			return (FALSE);
	}
	return (TRUE);
}

void	print_filled_variable(void *content)
{
	if (((t_variable *)content)->value
		&& ((t_variable *)content)->value[0])
	{
		print_variable(content);
	}
}

void	print_variable(void *content)
{
	ft_putstr_fd(((t_variable *)content)->name, 1);
	ft_putchar_fd('=', 1);
	ft_putstr_fd(((t_variable *)content)->value, 1);
	ft_putchar_fd('\n', 1);
}
