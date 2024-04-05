/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:34:59 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/05 12:33:18 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isnum(nptr[i]))
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb * sign);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	*str = "15+46";
// 	printf("%d\n", ft_atoi(str));
// 	printf("%d\n", atoi(str));
// 	return (0);
// }
