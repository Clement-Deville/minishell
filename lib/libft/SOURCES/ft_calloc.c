/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:04:57 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (size && __INT_MAX__ / size < nmemb)
		return (0);
	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	s = malloc(nmemb * size);
	if (!s)
		return (0);
	ft_bzero(s, nmemb * size);
	return (s);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", (char *)ft_calloc(10, 0));
// 	printf("%s\n", (char *)calloc(10, 0));
// 	return (0);
// }
