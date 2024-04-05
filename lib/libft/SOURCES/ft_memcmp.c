/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:39:07 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (*(unsigned char *)(s1 + i - 1) - *(unsigned char *)(s2 + i - 1));
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char *str1 = "Hello je m'appelle Clement";
// 	char *str2 = "Hello je m'appelle Clement";
// 	char s[] = {-128, 0, 127, 0};
// 	char sCpy[] = {-128, 0, 127, 0};
// 	printf("%d\n", ft_memcmp(s, sCpy, 4));
// 	printf("%d\n", memcmp(s, sCpy, 4));
// }
