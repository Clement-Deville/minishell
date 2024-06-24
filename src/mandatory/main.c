/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 15:33:50 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_readline(void)
{
	if (get_ms()->line)
	{
		free(get_ms()->line);
		get_ms()->line = NULL;
	}
	if (get_ms()->exit == 130 && get_ms()->signal)
	{
		get_ms()->signal = FALSE;
		ft_printf("\n");
	}
	if (get_ms()->exit == 131 && get_ms()->signal)
	{
		get_ms()->signal = FALSE;
		ft_printf("Quit (core dumped)\n");
	}
	// Need
	get_ms()->balise = get_balise();
	if (get_ms()->balise)
		get_ms()->line = readline(get_ms()->balise);
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
}

int	init_minishell(void)
{
	t_mini_env	*ms;

	ms = get_ms();
	ms->parent = TRUE;
	while (1)
	{
		do_readline();
		if (get_ms()->line[0])
			add_history(get_ms()->line);
		if (!ft_tokenization(ms))
		{
			ft_handle_parse_err(ms);
			continue ;
		}
		init_parsing(ms);
		if (get_ms()->err.str)
		{
			get_ms()->f_or_nf = 1;
			ft_handle_parse_err(ms);
			continue ;
		}
		if (exec_here_doc(ms->nodes))
		{
			get_ms()->f_or_nf = 0;
			continue ;
		}
		start_exec(ms->nodes, &(ms->envlst));
		if (get_ms()->f_or_nf == 0)
		{
			ft_garbage(NULL, TRUE);
			ft_clear_token(get_ms()->tokens);
			ft_clear_parsing(get_ms()->nodes);
		}
		else
		{
			ft_garbage(NULL, TRUE);
			ft_clear_parsing(get_ms()->nodes);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	returned_val;

	returned_val = 0;
	(void)ac;
	(void)av;
	setup_signals();
	ft_init_env(env);
	init_minishell();
	returned_val = get_ms()->exit;
	ft_clean_ms();
	return (returned_val);
}
