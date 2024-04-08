/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:33:00 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/08 11:41:48 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_echo(char *str, t_bool nonewline)
{
	if (nonewline == TRUE)
	{
		ft_putstr_fd(str, 1);
		return (0);
	}
	else
	{
		ft_putstr_fd(str, 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
}
