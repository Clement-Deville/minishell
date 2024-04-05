/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:33:16 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static void	manage_negative(t_struct *param, int	*number)
{
	if (*number < 0)
	{
		ft_putchar_fd('-', 1);
		param->isnegatif = TRUE;
		if (*number != INT_MIN)
			*number *= -1;
	}
}

static int	sizenumber(t_struct *param, int number)
{
	int			size;

	size = 0;
	if (number == 0 && param->precision == 0)
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

static int	sizeprinted(t_struct *param, int number)
{
	int	size_printed;

	size_printed = sizenumber(param, number);
	if (number < 0)
		size_printed++;
	else
	{
		if (param->plus)
			size_printed++;
		else if (param->space)
			size_printed++;
	}
	return (size_printed);
}

static void	print(t_struct *param, int number)
{
	int			size_number;

	size_number = sizenumber(param, number);
	if (number >= 0 && param->plus)
		ft_putchar_fd('+', 1);
	if (number >= 0 && param->space)
		ft_putchar_fd(' ', 1);
	if (param->precision > size_number)
		field_width('0', param->precision - size_number, param);
	if (size_number)
	{
		if ((param->zero || param->precision > size_number)
			&& number == INT_MIN)
			putnbr_unsigned_fd(INT_MIN, 1);
		else
			ft_putnbr_fd(number, 1);
	}
	return ;
}

int	print_integer(t_struct *param, va_list *ptr)
{
	int	number;
	int	size_printed;

	number = va_arg(*ptr, int);
	size_printed = sizeprinted(param, number);
	if ((param->precision != -1 || param->minus) && param->zero)
		param->zero = FALSE;
	if (param->space && param->plus)
		param->space = FALSE;
	if (param->width && !param->minus && !param->zero)
		field_space_begin(param, size_printed, number);
	if (param->zero || param->precision > sizenumber(param, number))
		manage_negative(param, &number);
	if (param->width && !param->minus && param->zero)
		field_width('0', param->width - size_printed, param);
	print(param, number);
	param->count += size_printed;
	param->zero = FALSE;
	if (param->precision > size_printed)
		size_printed = param->precision;
	if (param->width && param->minus)
		field_width(' ', param->width - size_printed - param->isnegatif, param);
	return (0);
}
