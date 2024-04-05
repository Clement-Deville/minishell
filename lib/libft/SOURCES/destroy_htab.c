/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_htab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:15:59 by cdeville          #+#    #+#             */
/*   Updated: 2024/02/02 14:28:14 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

static void	del_string(void *str)
{
	if (str == NULL)
		return ;
	free(str);
	str = NULL;
}

void	destroy_htab(t_hash *htab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (htab[i].content)
		{
			if (htab[i].next)
			{
				ft_lstclear(&(htab[i].next), &del_string);
			}
			del_string(htab[i].content);
		}
		i++;
	}
	free(htab);
	htab = NULL;
}
