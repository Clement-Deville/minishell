/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:28:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/03 11:59:37 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_parse_new(void)
{
	ft_printf("\033[D\033[D\033[K\n");
	get_ms()->exit = 130;
	print_balise(get_ms()->exit);
	get_ms()->signal = TRUE;
	// print_balise(0);
	// init_minishell();
}

void	do_nothing(void)
{
	get_ms()->signal = TRUE;
}
void	handle_signal(int signo)
{
	// ft_printf("I catch signal: %d\n", signo);
	if (signo == SIGINT)
		do_parse_new();
	if (signo == SIGQUIT)
	{
		do_nothing();
	}
}

void	handle_signal_child(int signo)
{
	// ft_printf("I catch signal: %d\n", signo);
	if (signo == SIGINT)
	{
		//clear envi
		exit (130);
	}
	if (signo == SIGQUIT)
	{
		//clear envi
		exit (get_ms()->exit);
	}
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
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	if (sigaction(SIGQUIT, &ignore, NULL) == -1)
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

	def.sa_handler = handle_signal;
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
