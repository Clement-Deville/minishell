/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:42:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/22 12:52:56 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_digit(char c)
{
	if ((c >= 48 && c <= 57))
		return (TRUE);
	return (FALSE);
}

t_bool	is_numeric(char *argument)
{
	while (*argument)
	{
		if (is_digit(*argument) == FALSE)
			return (FALSE);
		argument++;
	}
	return (TRUE);
}

int	do_exit(char *argument)
{
	if (argument == NULL)
		return (0);
	if (is_numeric(argument) == FALSE)
	{
		ft_printf("exit: %s: numeric argument required\n", argument);
		return (2);
	}
	return ((unsigned char)ft_atoi(argument));
}
