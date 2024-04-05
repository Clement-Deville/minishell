/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:46:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static int	isset(const char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	sizer(const char *s, const char *set)
{
	int	size;
	int	i;

	size = ft_strlen(s);
	i = size - 1;
	while (isset(s[i], set))
	{
		size--;
		i--;
		if (size == 0)
			return (0);
	}
	i = 0;
	while (s[i] && isset(s[i], set))
	{
		i++;
		size--;
		if (size == 0)
			return (0);
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*dest;
	size_t		i;
	size_t		size;

	i = 0;
	if (!s1)
		return (NULL);
	size = sizer(s1, set);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (s1[i] && isset(s1[i], set))
		i++;
	ft_strlcpy(dest, &s1[i], (size + 1));
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s = "   xxxtripouillex";
// 	char	*set = " x";

// 	printf("%s\n", ft_strtrim(s, set));
// 	printf("%s\n", ft_strtrim("", ""));
// 	return (0);
// }
