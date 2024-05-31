/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:42:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/31 15:40:59 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_digit(char c)
{
	if ((c >= 48 && c <= 57))
		return (TRUE);
	return (FALSE);
}

t_bool	is_numeric(char *argument)
{
	while (*argument)
	{
		if (is_digit(*argument) == FALSE)
			return (FALSE);
		argument++;
	}
	return (TRUE);
}

int	do_exit(t_node *node)
{
	char	*argument;

	argument = node->c_cmd->expand[1];
	if (argument == NULL)
		exit (0);
	if (is_numeric(argument) == FALSE)
	{
		if (node->silent == FALSE)
			ft_printf("exit: %s: numeric argument required\n", argument);
		// A print sur stderr
		return (2);
	}
	//DOIT AFFICHER EXIT DANS LE PARENT
	exit ((unsigned char)ft_atoi(argument));
}
