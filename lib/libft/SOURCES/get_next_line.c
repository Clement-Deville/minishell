/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:39:11 by cdeville          #+#    #+#             */
/*   Updated: 2024/02/27 20:26:35 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	trim_begining(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			ft_memmove(str, &str[i], BUFFER_SIZE - i);
			str[BUFFER_SIZE - i] = 0;
			return ;
		}
		i++;
	}
}

t_bool	isline_over(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_free(char **stock, char **line)
{
	if (stock && *stock)
	{
		free(*stock);
		*stock = NULL;
	}
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	return (0);
}

char	*fill_line(int fd, char *line, char **stock)
{
	int		number_read;

	while (!isline_over(line))
	{
		number_read = read(fd, stock[fd], BUFFER_SIZE);
		if (number_read == -1)
			return (gnl_free(&stock[fd], &line));
		stock[fd][number_read] = 0;
		if (number_read == 0)
		{
			if (ft_strlen(line) == 0)
				return (gnl_free(&stock[fd], &line));
			return (line);
		}
		line = ft_strjoin_edited(line, stock[fd]);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock[1024];

	if (!(fd >= 0 && fd <= 1023))
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = 0;
	if (stock[fd])
		line = ft_strjoin_edited(line, stock[fd]);
	else
		stock[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stock[fd])
		return (gnl_free(&stock[fd], &line));
	line = fill_line(fd, line, stock);
	if (!line)
		return (0);
	trim_begining(stock[fd]);
	return (line);
}
// #include <stdio.h>
// #include <fcntl.h>

// int main ()
// {
// 	int		fd;
// 	char	*lign;

// 	fd = open("test_empty.txt", O_RDONLY);
// 	lign = get_next_line(fd);
// 	while (lign)
// 	{
// 		printf("%s\n", lign);
// 		free(lign);
// 		lign = get_next_line(fd);
// 	}
// 	return (0);
// }
