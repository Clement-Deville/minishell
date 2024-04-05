/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:02:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;

	j = 0;
	i = 0;
	if (dst)
		i = ft_strlen(dst);
	len_dest = i;
	if (i >= size)
		return (size + ft_strlen(src));
	while (i < (size - 1) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (len_dest + ft_strlen(src));
}

// #include <stdio.h>
// #include <bsd/string.h>

// int	main(void)
// {
// 	// int	r;
// 	// char dest[30]; memset(dest, 0, 30);
// 	// char * src = (char *)"AAAAAAAAA";
// 	// dest[0] = 'B';
// 	// // ft_strlcat(dest, src, 0);
// 	// r = strlcat(dest, src, 0);
// 	// dest[0] = 'B';
// 	// // ft_strlcat(dest, src, 1);
// 	// r = strlcat(dest, src, 1);
// 	// memset(dest, 'B', 4);
// 	// // ft_strlcat(dest, src, 3);
// 	// r = strlcat(dest, src, 3);
// 	// // ft_strlcat(dest, src, 6);
// 	// r = strlcat(dest, src, 6);
// 	printf("%d\n", (int)ft_strlcat(NULL, "as", 0));
// 	printf("%d\n", (int)strlcat(NULL, "as", 0));
// 	return (0);
// }
