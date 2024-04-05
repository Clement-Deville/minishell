/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:03:58 by cdeville          #+#    #+#             */
/*   Updated: 2023/11/14 16:17:11 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*chr;

	i = 0;
	chr = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			chr = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		chr = (char *)&s[i];
	return (chr);
}
