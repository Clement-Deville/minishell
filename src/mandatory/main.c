/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/10 18:31:48 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_mini_env	ms;
	char		*line;
	t_node		*curr_node;
	t_token		*tmp_token;

	(void)ac;
	(void)av;
	line = get_next_line(0);
	ft_init_env(env, &ms, line);
	ft_tokenization(&ms);
	ft_parser(&ms);
	curr_node = ms.ast;
	while (curr_node != NULL)
	{
		ft_printf("Type :%d -- value : %s\n ", curr_node->type,
			curr_node->args);
		curr_node = curr_node->next;
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
