/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:48:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	reset(t_struct *param)
{
	param->hashtag = FALSE;
	param->zero = FALSE;
	param->minus = FALSE;
	param->space = FALSE;
	param->plus = FALSE;
	param->width = 0;
	param->identifier = 0;
	param->precision = -1;
	param->is_null = FALSE;
	param->isnegatif = FALSE;
}
