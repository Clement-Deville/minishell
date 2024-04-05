/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:57:28 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!ft_strlen(little))
		return ((char *)big);
	while (i < len && big[i])
	{
		if (little[j] == big[i])
		{
			while (little[j] == big[i] && i < len)
			{
				if (!little[j + 1])
					return ((char *)&big[i - j]);
				i++;
				j++;
			}
			i -= j;
			j = 0;
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <bsd/string.h>

// int	main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	printf("%s\n", ft_strnstr(haystack, "aaabc", 5));
// 	printf("%s\n", strnstr(haystack, "aaabc", 5));
// 	return (0);
// }
