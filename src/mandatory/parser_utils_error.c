/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:28:12 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/04 17:16:54 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_set_parse_err(t_err_parse type)
{
	get_ms()->err.type = type;
	get_ms()->err.str = "ERROR";
}

void	ft_handle_parse_err(t_mini_env *ms)
{
	t_err_parse			type;
	t_token_type		token_type;
	char				**types;

	types = (char *[]){"TOKEN_ELSE",
		"<", ">", "|", "&&", "||", "newline", "<<", ">>", "(", ")"};
	type = get_ms()->err.type;
	if (type)
	{
		if (type == E_SYNTAX)
		{
			if (!get_ms()->tmp)
				token_type = TOKEN_NULL;
			else
				token_type = get_ms()->tmp->type;
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(types[token_type], 2);
			ft_putstr_fd("'\n", 2);
			get_ms()->exit = 258;
		}
		ft_clear_token(ms->tokens);
		ft_bzero(&(get_ms()->err), sizeof(t_parser_error));
	}
}
