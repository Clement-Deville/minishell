/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:59:15 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 16:01:05 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_variable(void *content)
{
	ft_putstr_fd(((t_variable *)content)->name, 1);
	ft_putchar_fd('=', 1);
	ft_putstr_fd(((t_variable *)content)->value, 1);
	ft_putchar_fd('\n', 1);
}
