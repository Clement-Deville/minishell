/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:38:52 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static char	*empty(char	*str)
{
	str = (char *)malloc(sizeof(char));
	str[0] = 0;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	sub = NULL;
	if (!s || !len)
		return (empty(sub));
	size = ft_strlen(s);
	if (start > size)
		return (empty(sub));
	size = size - start;
	if (size > len)
		size = len;
	sub = (char *)malloc((size + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, &s[start], size + 1);
	return (sub);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *str = "tripouille";
// 	printf("%s\n", ft_substr(str, 1, 1));
// 	return (0);
// }
