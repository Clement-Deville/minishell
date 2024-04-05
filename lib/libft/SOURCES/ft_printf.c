/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:26:03 by cdeville          #+#    #+#             */
/*   Updated: 2024/02/20 17:23:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static int	check_flag(const char *s, t_struct *param)
{
	int	i;

	i = 0;
	while (isflag(s[i]))
	{
		if (s[i] == '#')
			param->hashtag = TRUE;
		else if (s[i] == '0')
			param->zero = TRUE;
		else if (s[i] == '-')
			param->minus = TRUE;
		else if (s[i] == ' ')
			param->space = TRUE;
		else if (s[i] == '0')
		{
			if (param->zero == TRUE)
				break ;
			param->zero = TRUE;
		}
		else if (s[i] == '+')
			param->plus = TRUE;
		i++;
	}
	return (i);
}

static int	check_ident(const char *s, t_struct *param)
{
	int	i;

	i = 1;
	if ((s[i]) == '%')
	{
		print_percent(param);
		return (i + 1);
	}
	i += check_flag(&s[i], param);
	param->width = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.')
	{
		i++;
		if (s[i] == '0')
			param->precision = 0;
		else
			param->precision = ft_atoi(&s[i]);
		while (ft_isdigit(s[i]))
			i++;
	}
	param->identifier = s[i];
	return (i + 1);
}

int	ft_printf(const char *str, ...)
{
	va_list		ptr;
	t_struct	param;

	reset(&param);
	param.count = 0;
	if (!str)
		return (-1);
	va_start(ptr, str);
	while (*str)
	{
		if (*str == '%')
		{
			str += check_ident(str, &param);
			print_parameter(&param, &ptr);
		}
		else
		{
			ft_putchar_fd(*str, 1);
			param.count += 1;
			str++;
		}
	}
	va_end(ptr);
	return (param.count);
}
