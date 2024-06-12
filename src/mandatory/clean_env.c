/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:41:03 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/12 18:52:08 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_variable(void *content)
{
	t_variable	*var;

	var = (t_variable *)content;
	free(var->name);
	free(var->value);
	free(var);
}

void	ft_clear_envlst(t_mini_env *mini_s)
{
	if (mini_s->envlst)
		ft_dblstclear(&mini_s->envlst, free_variable);
}

void	ft_clean_ms(void)
{
	ft_garbage(NULL, TRUE);
	ft_clear_token(get_ms()->tokens);
	ft_clear_parsing(get_ms()->nodes);
	ft_clear_envlst(get_ms());
	get_ms()->nodes = NULL;
}
