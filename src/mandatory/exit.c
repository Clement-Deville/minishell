/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:42:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 09:20:24 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_digit(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	is_numeric(char *argument)
{
	if ((*argument == '+' || *argument == '-') && is_digit(argument + 1))
		argument++;
	while (*argument)
	{
		if (is_digit(argument) == FALSE)
			return (FALSE);
		argument++;
	}
	return (TRUE);
}

int	print_error_numeric(t_node *node, char *argument)
{
	if (node->silent == FALSE)
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argument, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	// A print sur stderr
	return (2);
}

int	do_exit(t_node *node)
{
	char			*argument;
	unsigned char	exit_value;

	argument = node->c_cmd->expand[1];
	if (argument == NULL)
	{
		if (get_ms()->parent == TRUE && node->silent == FALSE)
			ft_putendl_fd("exit", 2);
		exit(clean_and_exit (0));
	}
	if (is_numeric(argument) == FALSE)
	{
		print_error_numeric(node, argument);
		exit(clean_and_exit (2));
	}
	else if (nbr_of_args(node->c_cmd->expand) > 1)
	{
		if (node->silent == FALSE)
			ft_putendl_fd("exit\nexit: too many arguments", 2);
		// A print sur stderr
		return (1);
	}
	//DOIT AFFICHER EXIT DANS LE PARENT
	if (get_ms()->parent == TRUE && node->silent == FALSE)
		ft_putendl_fd("exit", 2);
	exit_value = (unsigned char)ft_atoi(argument);
	exit(clean_and_exit (exit_value));
	// DOIT EXIT MEME SI LES ARG SONT MAUVAIS
}


// Si le premier n'est pas numerique alors ca exit quand meme

// S'il y a trop d'arguments et que le premier est valide alors il n'exit pas
