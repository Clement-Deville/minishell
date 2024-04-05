/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:52:46 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	field_width(char c, int size, t_struct *param)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
	if (size > 0)
		param->count += size;
}

void	field_space_begin(t_struct *param, int size_printed, int number)
{
	int	spaces;

	spaces = 0;
	if (param->precision > size_printed)
	{
		spaces = param->width - param->precision;
		if (param->precision < param->width && number < 0
			&& (param->identifier == 'd' || param->identifier == 'i'))
			spaces--;
	}
	else
		spaces = param->width - size_printed;
	return (field_width(' ', spaces, param));
}
