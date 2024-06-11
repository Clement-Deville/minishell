/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:23:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/11 13:15:27 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_variable(void *content)
{
	ft_putstr_fd(((t_variable *)content)->name, 1);
	ft_putchar_fd('=', 1);
	ft_putstr_fd(((t_variable *)content)->value, 1);
	ft_putchar_fd('\n', 1);
}

t_dblist	*generate_env(char **envp)
{
	t_dblist	*my_env;
	t_dblist	*new;
	int			i;

	i = 0;
	my_env = NULL;
	if (envp[i])
		my_env = ft_dblstnew(create_variable(envp[i++]));
	if (my_env == NULL || my_env->content == NULL)
		return (free(my_env), NULL);
	while (envp[i])
	{
		new = ft_dblstnew(create_variable(envp[i]));
		if (new == NULL || new->content == NULL)
			return (ft_dblstclear(&my_env, free), free(new), NULL);
		ft_dblstadd_back(&my_env, new);
		i++;
	}
	return (my_env);
}

int	do_env(t_dblist *my_env)
{
	ft_dblst_iter(my_env, print_variable);
	return (0);
	// Modifier pour afficher une erreur si argument
}
