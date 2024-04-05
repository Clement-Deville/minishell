/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:35:03 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/04 18:40:57 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

// It doesnt copy the exact behavior of atof function:
// - When 

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

double	ft_atof(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;

	sign = 1.0;
	int_part = 0.0;
	dec_part = 0.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign *= -1;
	while (ft_isnum(*str))
	{
		int_part = int_part * 10 + *str - 48;
		str++;
	}
	i = -1;
	if (*str && *(str++) == '.')
		while (ft_isnum(*str))
			dec_part += pow(10, i--) * (*(str++) - '0');
	return (sign * (int_part + dec_part));
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	double	nb;
// 	double	test;

// 	nb = ft_atof(av[1]);
// 	test = atof(av[1]);
// 	printf("ft_atof: %lf\n", nb);
// 	printf("Real atof: %lf\n", test);
// 	return (0);
// }
