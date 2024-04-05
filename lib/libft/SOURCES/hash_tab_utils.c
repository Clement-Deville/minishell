/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tab_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:26:58 by cdeville          #+#    #+#             */
/*   Updated: 2024/02/02 14:28:14 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	init_htab(t_hash *htab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		htab[i].content = NULL;
		htab[i].next = NULL;
		i++;
	}
}

static char	*insert_key(char *key)
{
	return (ft_strdup(key));
}

int	handle_collision(t_hash *htab, char *key)
{
	t_hash	*actual;

	actual = htab;
	while (actual)
	{
		if (actual->content == NULL)
		{
			actual->content = insert_key(key);
			if (actual->content == NULL)
				return (-2);
			return (0);
		}
		if ((!ft_strncmp(actual->content, key, ft_strlen(actual->content) + 1)))
			return (-1);
		else if (actual->next == NULL)
		{
			actual->next = (t_hash *)malloc(sizeof(t_hash));
			if (actual->next == NULL)
				return (-2);
			init_htab(actual->next, 1);
		}
		actual = actual->next;
	}
	return (0);
}
