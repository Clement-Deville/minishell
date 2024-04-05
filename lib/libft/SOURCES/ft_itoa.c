/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:23:52 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static int	nbrsize(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*nbr;
	long	ln;

	ln = (long)n;
	size = nbrsize(ln);
	nbr = (char *)malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (0);
	if (ln == 0)
		nbr[0] = '0';
	if (ln < 0)
	{
		ln *= -1;
		nbr[0] = '-';
	}
	nbr[size] = 0;
	while (ln)
	{
		nbr[size - 1] = ln % 10 + 48;
		ln /= 10;
		size--;
	}
	return (nbr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	i;
// 	char	*s;

// 	i = 20808;
// 	s = ft_itoa(i);
// 	printf("%s\n", s);
// 	free(s);
// 	return (0);
// }
