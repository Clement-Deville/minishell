/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:21:50 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 17:29:17 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_signal_handler_int(void)
{
	get_ms()->signal_int = TRUE;
	get_ms()->wait_interrupted = TRUE;
}

void	wait_signal_handler_quit(void)
{
	get_ms()->signal_quit = TRUE;
	get_ms()->wait_interrupted = TRUE;
}

void	wait_handler(int signo)
{
	if (signo == SIGINT)
		wait_signal_handler_int();
	if (signo == SIGQUIT)
		wait_signal_handler_quit();
}

void	handle_signal(int signo)
{
	char	*new_prompt;

	if (signo == SIGINT)
	{
		get_ms()->exit = 130;
		new_prompt = get_balise();
		if (new_prompt == NULL)
			exit(clean_and_exit(1));
		rl_set_prompt(new_prompt);
		ft_printf("\n");
		rl_on_new_line ();
		rl_replace_line("", 0);
		rl_redisplay();
		free(new_prompt);
	}
	if (signo == SIGQUIT)
	{
		free(get_ms()->line);
		get_ms()->line = NULL;
	}
}

void	handle_signal_child(int signo)
{
	if (signo == SIGINT)
		exit (clean_and_exit(130));
	if (signo == SIGQUIT)
		exit (clean_and_exit(131));
}
