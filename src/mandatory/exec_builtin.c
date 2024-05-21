/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:59:11 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/20 11:19:39 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **args)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (do_echo(args));
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (do_cd(args[1], get_ms()->envlst));
	// if (ft_strcmp(args[0], "env") == 0)
	// 	return (do_env());
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (do_pwd());
	// if (ft_strcmp(args[0], "export") == 0)
	// 	return (do_export(args));
	// if (ft_strcmp(args[0], "unset") == 0)
	// 	return (do_unset(args));
	// do_exit(args);
	ft_printf("NOT DONE YET");
	return (ENO_GENERAL);
}

int	ft_is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, "echo", ft_strlen(arg))
		|| !ft_strncmp(arg, "cd", ft_strlen(arg))
		|| !ft_strncmp(arg, "exit", ft_strlen(arg))
		|| !ft_strncmp(arg, "pwd", ft_strlen(arg))
		|| !ft_strncmp(arg, "export", ft_strlen(arg))
		|| !ft_strncmp(arg, "unset", ft_strlen(arg))
		|| !ft_strncmp(arg, "env", ft_strlen(arg)))
		return (1);
	return (0);
}
