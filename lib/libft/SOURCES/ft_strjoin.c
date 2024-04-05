/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:22:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (*s1)
	{
		dest[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		dest[i] = *s2;
		s2++;
		i++;
	}
	dest[i] = 0;
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *s1 = "Bonjour";
// 	char *s2 = "";
// 	printf("%s", ft_strjoin(s1, s2));
// 	return (0);
// }
