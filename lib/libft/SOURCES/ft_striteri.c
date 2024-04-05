/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:05:24 by cdeville          #+#    #+#             */
/*   Updated: 2023/11/15 17:59:37 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

// char	road1(unsigned int i, char* c)
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
