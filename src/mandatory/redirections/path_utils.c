/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:59:30 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 12:00:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (0);
	while (split[i])
		i++;
	return (i);
}

char	*get_path(t_dblist *env)
{
	while (env)
	{
		if (ft_strncmp("PATH", ((t_variable *)(env->content))->name, 5) == 0)
			return (((t_variable *)(env->content))->value);
		env = env->next;
	}
	return (NULL);
}
