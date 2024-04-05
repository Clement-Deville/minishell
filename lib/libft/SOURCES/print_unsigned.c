/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:41:17 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static int	sizenumber(t_struct *param, unsigned int number)
{
	int	size;

	size = 0;
	if (param->precision == 0 && number == 0)
		return (0);
	if (number == 0)
		return (1);
	while (number)
	{
		number /= 10;
		size++;
	}
	return (size);
}

static void	print(t_struct *param, unsigned int number)
{
	int	size_number;

	size_number = sizenumber(param, number);
	if (param->precision > size_number)
		field_width('0', param->precision - size_number, param);
	if (size_number)
		putnbr_unsigned_fd(number, 1);
	return ;
}

int	print_unsigned(t_struct *param, va_list *ptr)
{
	unsigned int	number;
	int				size_printed;

	number = va_arg(*ptr, unsigned int);
	size_printed = sizenumber(param, number);
	if ((param->precision != -1 || param->minus) && param->zero)
		param->zero = FALSE;
	if (param->width && !param->minus && !param->zero)
		field_space_begin(param, size_printed, number);
	if (param->width && !param->minus && param->zero)
		field_width('0', param->width - size_printed, param);
	print(param, number);
	param->count += size_printed;
	param->zero = FALSE;
	if (param->precision > size_printed)
		size_printed = param->precision;
	if (param->width && param->minus)
		field_width(' ', param->width - size_printed, param);
	return (0);
}
