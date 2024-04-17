/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/17 17:17:07 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*convert_type(t_node_type type);
char	*convert_type2(t_red_type type);

int	main(int ac, char **av, char **env)
{
	t_mini_env	ms;
	char		*line;
	t_node		*ast_node;
	t_token		*tmp_token;
	int			i = 0;

	(void)ac;
	(void)av;
	line = get_next_line(0);
	ft_init_env(env, &ms, line);
	ft_tokenization(&ms);
	ms.ast = ft_parser(&ms, &i, ms.tokens);
	ast_node = ms.ast;
	// if (!ast_node->type)
	// {
	if (ast_node->red_node)
		ft_printf("Type :%s -- value : %s\n ", convert_type2(ast_node->red_node->type),
		ast_node->red_node->value);
	// }
	else
		ft_printf("Type :%s -- value : %s\n ", convert_type(ast_node->type),
			ast_node->args);
	if (ast_node->next && ast_node->next->args)
		ft_printf("Type :%s -- value : %s\n ", convert_type(ast_node->next->type),
			ast_node->next->args);
	if (ast_node->prev)
		ft_printf("Type :%s -- value : %s\n ", convert_type(ast_node->prev->type),
			ast_node->prev->args);
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
