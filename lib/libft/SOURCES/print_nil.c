/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:07:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

int	print_nil(t_struct *param, char *str)
{
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(str);
	if (param->precision != -1 && param->precision < size)
		size = param->precision;
	if (!param->minus)
		field_width(' ', param->width - size, param);
	while (i < size)
		ft_putchar_fd(str[i++], 1);
	param->count += size;
	if (param->minus)
		field_width(' ', param->width - size, param);
	return (0);
}
