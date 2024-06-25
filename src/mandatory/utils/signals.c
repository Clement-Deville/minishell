/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:28:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/25 11:47:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_signals(void)
{
	if (get_ms()->signal_int)
		exit(clean_and_exit (130));
	if (get_ms()->signal_quit)
		exit(clean_and_exit (131));
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
