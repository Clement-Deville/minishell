/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/25 10:45:44 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cleaning_routine(void)
{
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

t_bool	check_and_handle_error(void)
{
	if (get_ms()->err.str)
	{
		get_ms()->f_or_nf = 1;
		ft_handle_parse_err(get_ms());
		return (TRUE);
	}
	return (FALSE);
}

int	init_minishell(void)
{
	get_ms()->parent = TRUE;
	while (1)
	{
		do_readline();
		if (get_ms()->line[0])
			add_history(get_ms()->line);
		if (!ft_tokenization(get_ms()))
		{
			ft_handle_parse_err(get_ms());
			continue ;
		}
		init_parsing(get_ms());
		if (check_and_handle_error())
			continue ;
		if (exec_here_doc(get_ms()->nodes))
		{
			get_ms()->f_or_nf = 0;
			continue ;
		}
		start_exec(get_ms()->nodes, &(get_ms()->envlst));
		cleaning_routine();
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
