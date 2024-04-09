/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:23:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 16:01:05 by cdeville         ###   ########.fr       */
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

void	destroy_variable(t_variable *variable)
{
	if (variable)
	{
		free(variable->name);
		free(variable->value);
	}
	free(variable);
}

char	*get_name(char *argument)
{
	char	*name;
	int		size;

	size = 0;
	while (argument[size] && argument[size] != '=')
		size++;
	name = (char *)malloc((size + 1) * sizeof(char));
	if (name == NULL)
		return (NULL);
	name = ft_memcpy(name, argument, size);
	return (name);
}

char	*get_value(char *argument)
{
	char	*value;
	int		i;

	i = 0;
	while (argument[i] && argument[i] != '=')
		i++;
	value = ft_strdup(&argument[++i]);
	if (value == NULL)
		return (NULL);
	return (value);
}

t_variable	*create_variable(char *argument)
{
	t_variable	*variable;

	variable = (t_variable *)malloc(sizeof(t_variable));
	if (variable == NULL)
		return (perror("Malloc error"), NULL);
	variable->name = get_name(argument);
	if (variable->name == NULL)
		return (perror("Malloc error"), free(variable), NULL);
	variable->value = get_value(argument);
	if (variable->value == NULL)
		return (perror("Malloc error"), free(variable->name), free(variable), NULL);
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
	ft_dblst_iter(my_env, print_variable);
	return (0);
}
