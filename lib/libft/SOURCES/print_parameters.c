/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:21:53 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	print_parameter(t_struct *param, va_list *ptr)
{
	if (param->identifier == 'd' || param->identifier == 'i')
		print_integer(param, ptr);
	else if (param->identifier == 'u')
		print_unsigned(param, ptr);
	else if (param->identifier == 'x' || param->identifier == 'X')
		print_hexa(param, ptr);
	else if (param->identifier == 'p')
		print_pointer(param, ptr);
	else if (param->identifier == 'c')
		print_char(param, ptr);
	else if (param->identifier == 's')
		print_string(param, ptr);
	reset(param);
}
