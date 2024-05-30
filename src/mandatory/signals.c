/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:28:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/30 19:06:18 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_parse_new(void)
{
	ft_printf("\033[D\033[D\033[K\n");
	get_ms()->exit = 130;
	print_balise(get_ms()->exit);
	// print_balise(0);
	// init_minishell();
}

int	test(void)
{
	ft_printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	exit (1);
}
void	handle_signal(int signo)
{
	ft_printf("I catch signal: %d\n", signo);
	if (signo == SIGINT)
		do_parse_new();
	if (signo == SIGQUIT)
	{
		test();
	}
}

void	handle_signal_child(int signo)
{
	ft_printf("I catch signal: %d\n", signo);
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

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error sigaction");
		return (1);
	}
	return (0);
}
