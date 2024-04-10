/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/10 18:35:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_dblist	*enviro;
	char		*args[4];

	args[0] = "TEST=yes";
	args[1] = "BOSS=ZILEAN";
	args[2] = "TEST=yo";
	args[3] = NULL;
	(void)ac;
	(void)av;
	enviro = generate_env(env);
	if (enviro == NULL)
		return (1);
	do_export(args, enviro);
	do_export(NULL, enviro);
	do_unset(args, enviro);
	do_cd("../pipex", enviro);
	do_export(NULL, enviro);
	ft_dblstclear(&enviro, &destroy_variable);
	return (0);
}
