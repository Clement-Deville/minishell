/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:23:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = malloc(ft_strlen(s) + 1);
	if (!dest)
		return (0);
	return (ft_memcpy(dest, s, ft_strlen(s) + 1));
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*str = "";

// 	printf("%s\n", ft_strdup(str));
// 	printf("%s\n", strdup(str));
// 	return (0);
// }
