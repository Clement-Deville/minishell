/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:43:39 by cdeville          #+#    #+#             */
/*   Updated: 2023/11/14 16:15:55 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char s[] = "tripouille";
// 	printf("%s\n", ft_strchr(s, 't' + 256));
// 	printf("%s\n", strchr(s, 't' + 256));
// }
