/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:28:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 16:17:35 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_parse_new(void)
{
	char	*new_prompt;

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

void	do_nothing(void)
{
	free(get_ms()->line);
	get_ms()->line = NULL;
}
void	handle_signal(int signo)
{
	if (signo == SIGINT)
		do_parse_new();
	if (signo == SIGQUIT)
		do_nothing();
}

void	handle_signal_child(int signo)
{
	// ft_printf("I catch signal: %d\n", signo);
	if (signo == SIGINT)
		exit (clean_and_exit(130));
	if (signo == SIGQUIT)
		exit (clean_and_exit(131));
}

int	setup_signals(void)
{
	struct sigaction	sa;
	struct sigaction	ignore;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	(void)ignore;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	return (0);
}

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

int	set_wait_signals(void)
{
	struct sigaction	sa;
	struct sigaction	ignore;

	sa.sa_handler = wait_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	(void)ignore;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	return (0);
}

int	set_ignore_signals(void)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	if (sigaction(SIGINT, &ignore, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	if (sigaction(SIGQUIT, &ignore, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	return (0);
}

int	set_child_signals(void)
{
	struct sigaction	def;

	def.sa_handler = handle_signal_child;
	sigemptyset(&def.sa_mask);
	def.sa_flags = 0;
	if (sigaction(SIGINT, &def, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	if (sigaction(SIGQUIT, &def, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	return (0);
}

