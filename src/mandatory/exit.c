/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:42:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/11 16:09:08 by cdeville         ###   ########.fr       */
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
	while (*argument)
	{
		if (is_digit(argument) == FALSE)
			return (FALSE);
		argument++;
	}
	return (TRUE);
}

// int	do_exit(char *argument)
// {
// 	if (*argument == 0)
// 		return (0);
// 	if (is_numeric(argument) == FALSE)
// 	{
// 		ft_printf("exit: %s: numeric argument required\n", argument);
// 		return (2);
// 	}
// 	return ((unsigned char)ft_atoi(argument));
// }

// static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
// {
// 	while (s[*i] && s[*i] == ' ')
// 		(*i)++;
// 	if (s[*i] == '+' || s[*i] == '-')
// 	{
// 		if (s[*i] == '-')
// 			*sign *= -1;
// 		(*i)++;
// 	}
// }

// static int	ft_exittoi(char *s)
// {
// 	int					i;
// 	int					sign;
// 	int					exit_s;
// 	unsigned long long	result;

// 	i = 0;
// 	sign = 1;
// 	ft_skip_spaces_and_get_sign(s, &i, &sign);
// 	if (!is_digit(s + i))
// 	{
// 		exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
// 		(ft_clean_ms(), exit(exit_s));
// 	}
// 	result = 0;
// 	while (s[i])
// 	{
// 		result = (result * 10) + (s[i] - '0');
// 		if (result > LONG_MAX)
// 		{
// 			exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
// 			(ft_clean_ms(), exit(exit_s));
// 		}
// 		i++;
// 	}
// 	return ((result * sign) % 256);
// }

// void	do_exit(char **args)
// {
// 	int	exit_s;

// 	exit_s = get_ms()->exit;
// 	if (args[1])
// 	{
// 		if (args[2] && is_digit(args[1]))
// 		{
// 			exit_s = ft_err_msg(
// 					(t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
// 			ft_clean_ms();
// 			exit(exit_s);
// 		}
// 		else
// 			exit_s = ft_exittoi(args[1]);
// 	}
// 	ft_clean_ms();
// 	exit(exit_s);
//	}

int	do_exit(t_node *node)
{
	char	*argument;

	argument = node->c_cmd->expand[1];
	if (argument == NULL)
	{
		if (get_ms()->parent == TRUE && node->silent == FALSE)
			ft_putendl_fd("exit", 2);
		exit (0);
	}
	if (is_numeric(argument) == FALSE)
	{
		if (node->silent == FALSE)
		{
			ft_printf("exit: %s: numeric argument required\n", argument);
		}
		// A print sur stderr
		exit (2);
	}
	if (nbr_of_args(node->c_cmd->expand) > 1)
	{
		if (node->silent == FALSE)
			ft_putendl_fd("exit: too many arguments", 2);
		// A print sur stderr
		return (1);
	}
	//DOIT AFFICHER EXIT DANS LE PARENT
	if (get_ms()->parent == TRUE && node->silent == FALSE)
		ft_putendl_fd("exit", 2);
	exit ((unsigned char)ft_atoi(argument));
	// DOIT EXIT MEME SI LES ARG SONT MAUVAIS
}
