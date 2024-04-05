/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:37:26 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static char	*set_null(t_struct *param)
{
	param->is_null = TRUE;
	return (ft_strdup((const char *)"(null)"));
}

int	print_string(t_struct *param, va_list *ptr)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	str = va_arg(*ptr, char *);
	if (!str && param->precision < 6 && param->precision != -1)
		return (0);
	if (!str)
		str = set_null(param);
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
	if (param->is_null == TRUE)
		free(str);
	return (0);
}
