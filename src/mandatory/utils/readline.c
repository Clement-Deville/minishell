/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:45:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/10/09 17:35:13 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	start_new_line(void)
{
	if (get_ms()->line)
	{
		free(get_ms()->line);
		get_ms()->line = NULL;
	}
	if (get_ms()->signal_int)
	{
		get_ms()->signal_int = FALSE;
		get_ms()->wait_interrupted = FALSE;
		ft_printf("\n");
	}
	if (get_ms()->signal_quit)
	{
		get_ms()->signal_quit = FALSE;
		get_ms()->wait_interrupted = FALSE;
		ft_printf("Quit (core dumped)\n");
	}
}

void	do_readline(void)
{
	start_new_line();
	get_ms()->balise = get_balise();
	if (get_ms()->balise)
	{
		get_ms()->line = readline(get_ms()->balise);
		clean_balise();
	}
	else if (get_ms()->exit)
		get_ms()->line = readline("\001\033[1;31m\002➜ \001\033[0m\002");
	else
		get_ms()->line = readline("\001\033[1;32m\002➜ \001\033[0m\002");
	if (get_ms()->line == NULL)
	{
		ft_putendl_fd("exit", 2);
		ft_clear_envlst(get_ms());
		exit (get_ms()->exit);
	}
	get_ms()->line_count++;
}
