/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:45:53 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 08:49:06 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_variable(t_variable *variable)
{
	char	*str;
	char	*temp;

	str = ft_strdup(variable->name);
	if (str == NULL)
		return (NULL);
	temp = str;
	str = ft_strjoin(str, "=");
	if (str == NULL)
		return (perror("Malloc"), free(temp), NULL);
	free(temp);
	temp = str;
	str = ft_strjoin(str, variable->value);
	if (str == NULL)
		return (perror("Malloc"), free(temp), NULL);
	return (free(temp), str);
}

char	**list_to_tab(t_dblist *env)
{
	char	**tab;
	int		i;
	int		size;

	size = dlst_size((env));
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (tab == NULL)
		return (perror("Malloc"), NULL);
	tab[size] = NULL;
	i = 0;
	while (env)
	{
		tab[i] = get_variable((t_variable*)(env->content));
		if (tab[i] == NULL)
		{
			while (i >= 0)
				free(tab[i--]);
			return (free(tab), NULL);
		}
		env = env->next;
		i++;
	}
	return (tab);
}

int	dlst_size(t_dblist *lst)
{
	t_dblist	*actual;
	int			count;

	if (!lst)
		return (0);
	count = 1;
	actual = lst;
	while (actual->next)
	{
		count++;
		actual = actual->next;
	}
	return (count);
}
