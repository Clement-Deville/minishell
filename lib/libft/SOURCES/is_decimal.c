/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:50:17 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/04 14:54:53 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 8 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_isnum(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

static t_bool	is_valid(char end, t_bool contain_int, t_bool contain_deci)
{
	if (end == 0 && contain_int == TRUE && contain_deci == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

t_bool	is_decimal(char *arg)
{
	int		i;
	t_bool	contain_int;
	t_bool	contain_deci;

	i = 0;
	contain_int = FALSE;
	contain_deci = FALSE;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	i++;
	while (ft_isnum(arg[i]))
	{
		contain_int = TRUE;
		i++;
	}
	if (arg[i] && arg[i++] == '.')
	{
		while (ft_isnum(arg[i]))
		{
			contain_deci = TRUE;
			i++;
		}
	}
	return (is_valid(arg[i], contain_int, contain_deci));
}
