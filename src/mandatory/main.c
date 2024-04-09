/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 19:07:33 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	// t_mini_env	ms;
	// char		*line;
	t_dblist	*enviro;
	char		*args[3];

	args[0] = "TEST=yes";
	args[1] = "BOSS=ZILEAN";
	args[2] = NULL;
	(void)ac;
	(void)av;
	enviro = generate_env(env);
	if (enviro == NULL)
		return (1);
	// do_env(enviro);
	do_export(args, enviro);
	do_export(NULL, enviro);
	// line = get_next_line(0);
	// ft_init_env(env, &ms, line);
	// ft_tokenization(&ms);
	// free(line);
	return (0);
}
