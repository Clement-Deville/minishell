/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:59:11 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/11 17:08:43 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **args, t_mini_env *ms)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (do_echo(args));
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (do_cd(args[1], get_ms()->envlst));
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (do_env(ms->envlst));
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (do_pwd());
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (do_export(args, ms->envlst));
	// if (ft_strncmp(args[0], "unset", ft_Strlen(args[0])) == 0)
	// 	return (do_unset(args));
	if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		do_exit(args);
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
