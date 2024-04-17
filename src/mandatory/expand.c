/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:50:37 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/17 20:07:35 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*do_expand(char *arg)
{
	char	*str;

	if (arg == NULL)
		return (NULL);
	if (*arg == 0)
	{
		str = ft_strdup("$");
		if (str == NULL)
			perror("Strdup error");
	}
	else if (name_exists(arg))
	{
		// duplicate
	}
	else
	{
		str = ft_strdup("");
		if (str == NULL)
			perror("Strdup error");
	}
	return (str);
}
