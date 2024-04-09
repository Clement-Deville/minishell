/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 21:50:47 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_mini_env	ms;
	char		*line;
	t_token		*curr_token;
	t_token		*tmp_token;

	(void)ac;
	(void)av;
	line = get_next_line(0);
	ft_init_env(env, &ms, line);
	ft_tokenization(&ms);
	curr_token = ms.tokens;
	while (curr_token != NULL)
	{
		ft_printf("Type :%d -- value : %s\n ", curr_token->type,
			curr_token->value);
		curr_token = curr_token->next;
	}
	free(line);
	while (ms.tokens != NULL)
	{
		tmp_token = ms.tokens;
		ms.tokens = ms.tokens->next;
		free(tmp_token->value);
		free(tmp_token);
	}
	return (0);
}
