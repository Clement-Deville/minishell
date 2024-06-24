/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:28:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 15:27:56 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_parse_new(void)
{
	char	*new_prompt;

	get_ms()->signal = TRUE;
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
	get_ms()->signal = TRUE;
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
		exit (clean_and_exit(get_ms()->exit));
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
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
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

