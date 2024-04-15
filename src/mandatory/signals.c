/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:28:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/15 17:47:37 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_parse_new(void)
{
	ft_printf("New prompt.\n");
}

void	handle_signal(int signo)
{
	ft_printf("I catch signal: %d\n", signo);
	if (signo == SIGINT)
		do_parse_new();
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
