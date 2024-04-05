/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:40:12 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/26 12:03:20 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_src;
	unsigned char	*ptr_dest;

	if (!dest && !src)
		return (NULL);
	ptr_src = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	while (n)
	{
		*ptr_dest = *ptr_src;
		ptr_src++;
		ptr_dest++;
		n--;
	}
	return (dest);
}

static void	*ft_rev_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_src;
	unsigned char	*ptr_dest;

	ptr_src = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	while (n)
	{
		*(ptr_dest + (n - 1)) = *(ptr_src + (n - 1));
		n--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	if (src < dest)
		return (ft_rev_memcpy(dest, src, n));
	return (dest);
}

char	*ft_strjoin_edited(char *line, char const *buff)
{
	char	*dest;
	int		i;

	i = 0;
	if (!line || !buff)
		return (NULL);
	dest = (char *)malloc(ft_strlen(line) + ft_strlen(buff) + 1);
	if (!dest)
		return (NULL);
	while (*line)
		dest[i++] = *(line++);
	free(line - i);
	while (*buff && *buff != '\n')
		dest[i++] = *(buff++);
	if (*buff == '\n')
	{
		dest[i] = '\n';
		dest[i + 1] = 0;
	}
	else
		dest[i] = 0;
	return (dest);
}
