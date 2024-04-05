/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:38:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

int	print_char(t_struct *param, va_list *ptr)
{
	if (param->width && !param->minus)
		field_width(' ', param->width - 1, param);
	ft_putchar_fd(va_arg(*ptr, int), 1);
	param->count += 1;
	if (param->width && param->minus)
		field_width(' ', param->width - 1, param);
	return (0);
}
