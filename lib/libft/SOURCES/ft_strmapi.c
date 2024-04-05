/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:45:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = 0;
	return (dest);
}

// char	road1(unsigned int i, char c)
// {
// 	(void)i;
// 	return (c + 1);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char 	*s = "12345678";
// 	void 	*f;
// 	char	*dest;
// 	f = &road1;
// 	dest = ft_strmapi(s, f);
// 	printf("%s\n", dest);
// 	free(dest);
// 	return (0);
// }
