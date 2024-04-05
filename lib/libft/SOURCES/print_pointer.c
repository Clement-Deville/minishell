/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:36:13 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static int	sizenumber(t_struct *param, size_t number)
{
	int	size;

	size = 0;
	if (number == 0)
		return (1);
	if (param->precision == 0 && number == 0)
		return (0);
	while (number)
	{
		number /= 16;
		size++;
	}
	return (size);
}

static int	sizeprinted(t_struct *param, size_t number)
{
	int	size_printed;

	size_printed = sizenumber(param, number);
	if (param->hashtag)
		size_printed += 2;
	return (size_printed);
}

static void	print_convert(t_struct *param, size_t decimal, char *base)
{
	if (decimal >= 16)
	{
		print_convert(param, decimal / 16, base);
	}
	ft_putchar_fd(base[decimal % 16], 1);
}

static void	print(t_struct *param, size_t number)
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

int	print_pointer(t_struct *param, va_list *ptr)
{
	size_t	p;
	int		sizeptrd;

	p = va_arg(*ptr, size_t);
	if (!p)
		return (print_nil(param, "(nil)"));
	param->identifier = 'x';
	param->hashtag = TRUE;
	if (!p)
		param->hashtag = FALSE;
	sizeptrd = sizeprinted(param, p);
	if ((param->precision != -1 || param->minus) && param->zero)
		param->zero = FALSE;
	if (param->width && !param->minus)
		field_width(' ', param->width - sizeptrd, param);
	print(param, p);
	param->count += sizeptrd;
	if (param->width && param->minus)
		field_width(' ', param->width - sizeptrd, param);
	return (0);
}
