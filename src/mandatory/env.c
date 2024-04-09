/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:23:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 10:59:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	number_of_variable(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	destroy_variable(t_env *variable)
{
	if (variable)
		free(variable->value);
}

t_env	*create_variable(char *str)
{
	t_env	*variable;

	variable = (t_env *)malloc(sizeof(t_env));
	if (variable == NULL)
		return (perror("Malloc error"), NULL);
	variable->value = ft_strdup(str);
	if (variable->value == NULL)
		return (perror("Malloc error"), free(variable), NULL);
	variable->export = FALSE;
	return (variable);
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
	ft_dblst_iter(my_env, print_env);
	return (0);
}
