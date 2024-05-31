/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:33:00 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/31 18:44:05 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	do_echo(char *str, t_bool nonewline)
// {
// 	if (nonewline == TRUE)
// 	{
// 		ft_putstr_fd(str, 1);
// 		return (0);
// 	}
// 	else
// 	{
// 		ft_putstr_fd(str, 1);
// 		ft_putchar_fd('\n', 1);
// 		return (0);
// 	}
// }

static int	ft_check_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	do_echo(char **args)
{
	int	i;
	int	opt;

	i = 1;
	opt = 0;
	// PROBLEME POUR ECHO -N
	while (args[i] != NULL && ft_check_option(args[i]) == 1)
	{
		opt = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (opt == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
