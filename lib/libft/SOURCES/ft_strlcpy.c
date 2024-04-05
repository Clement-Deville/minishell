/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:35:58 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

// #include <stdio.h>
// #include <bsd/string.h>

// int	main(void)
// {
// 	char	src[] = "coucou";
// 	char	dest[10];
// 	memset(dest, 'A', 10);
// 	// printf("%d\n",
// (ft_strlcpy(dest, src, 0) == strlen(src) && dest[0] == 'A'));
// 	printf("%d\n", (strlcpy(dest, src, 0) == strlen(src) && dest[0] == 'A'));
// 	return (0);
// }
