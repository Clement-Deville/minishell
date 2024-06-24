/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:15 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 08:46:25 by cdeville         ###   ########.fr       */
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

void	destroy_variable(void *content)
{
	t_variable	*variable;

	variable = (t_variable *)content;
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
	name[size] = 0;
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
	if (argument[i])
		i++;
	value = ft_strdup(&argument[i]);
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
	{
		perror("Malloc error");
		free(variable->name);
		free(variable);
		return (NULL);
	}
	return (variable);
}
