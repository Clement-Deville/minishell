/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:23:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/08 13:43:42 by cdeville         ###   ########.fr       */
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

char	**generate_env(char **envp)
{
	char	**env;
	int		i;
	int		size;

	i = 0;
	size = number_of_variable(envp);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (env == NULL)
		return (perror("Malloc error:"), NULL);
	env[size] = NULL;
	while (envp[i])
	{
		env[i] = strdup(envp[i]);
		if (env[i] == NULL)
		{
			perror("Malloc error:");
			while (i >= 0)
				free(env[i--]);
			return (NULL);
		}
		i++;
	}
	return (env);
}
