/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:24:52 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:21:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static void	reset_param(t_freeparam *param)
{
	param->pointer = FALSE;
	param->split = FALSE;
	param->list = FALSE;
	param->dblist = FALSE;
}

static int	check_ident(const char *s, t_freeparam *param)
{
	int	i;

	i = 1;
	if (!ft_strchr("psld", s[i]))
		return (1);
	if (s[i] == 'p')
		param->pointer = TRUE;
	if (s[i] == 's')
		param->split = TRUE;
	if (s[i] == 'l')
		param->list = TRUE;
	if (s[i] == 'd')
		param->dblist = TRUE;
	return (0);
}

static void	free_parameter(t_freeparam *param, va_list *ptr)
{
	if (param->pointer)
		free(va_arg(*ptr, void *));
	else if (param->split)
		free_split(va_arg(*ptr, char **));
	else if (param->list)
		ft_lstclear(va_arg(*ptr, t_list **), va_arg(*ptr, void *));
	else if (param->dblist)
		ft_dblstclear(va_arg(*ptr, t_dblist **), va_arg(*ptr, void *));
	reset_param(param);
}

int	ft_free(const char *str, ...)
{
	va_list		ptr;
	t_freeparam	param;

	reset_param(&param);
	if (!str)
		return (-1);
	va_start(ptr, str);
	while (*str)
	{
		if (*str != '%' && *str != ' ')
			return (write (1, "Error in ft_free args\n", 23));
		if (*str == '%' && (*str + 1))
		{
			if (check_ident(str, &param))
				return (-1);
			free_parameter(&param, &ptr);
			str += 2;
		}
		else if (*str == ' ')
			str++;
	}
	va_end(ptr);
	return (0);
}
