/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:34:10 by cdeville          #+#    #+#             */
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
		number /= 16;
		size++;
	}
	return (size);
}

static int	sizeprinted(t_struct *param, unsigned int number)
{
	int	size_printed;

	size_printed = sizenumber(param, number);
	if (param->hashtag)
		size_printed += 2;
	return (size_printed);
}

static void	print_convert(t_struct *param, unsigned int decimal, char *base)
{
	if (decimal >= 16)
	{
		print_convert(param, decimal / 16, base);
	}
	ft_putchar_fd(base[decimal % 16], 1);
}

static void	print(t_struct *param, unsigned int number)
{
	int	size_number;

	size_number = sizenumber(param, number);
	if (!size_number)
		return ;
	if (param->identifier == 'x')
	{
		if (param->hashtag)
			ft_putstr_fd("0x", 1);
		if (param->precision > size_number)
			field_width('0', param->precision - size_number, param);
		print_convert(param, number, HEXA_BASE_LOW);
	}
	if (param->identifier == 'X')
	{
		if (param->hashtag)
			ft_putstr_fd("0X", 1);
		if (param->precision > size_number)
			field_width('0', param->precision - size_number, param);
		print_convert(param, number, HEXA_BASE_UP);
	}
	return ;
}

int	print_hexa(t_struct *param, va_list *ptr)
{
	unsigned int	number;
	int				size_printed;

	number = va_arg(*ptr, unsigned int);
	if (!number)
		param->hashtag = FALSE;
	size_printed = sizeprinted(param, number);
	if ((param->precision != -1 || param->minus) && param->zero)
		param->zero = FALSE;
	if (param->width && !param->minus && !param->zero)
		field_space_begin(param, size_printed, number);
	if (param->width && !param->minus && param->zero)
		field_width('0', param->width - size_printed, param);
	print(param, number);
	param->count += size_printed;
	if (param->precision > size_printed)
		size_printed = param->precision;
	if (param->width && param->minus)
		field_width(' ', param->width - size_printed, param);
	return (0);
}
