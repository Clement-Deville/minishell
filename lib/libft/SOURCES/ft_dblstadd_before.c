/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstadd_before.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:50:39 by cdeville          #+#    #+#             */
/*   Updated: 2024/02/28 19:21:32 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

t_dblist	*ft_dblstadd_before(t_dblist *actual, t_dblist *new)
{
	if (!actual || !new)
		return (NULL);
	new->next = actual;
	new->prev = actual->prev;
	if (actual->prev)
		actual->prev->next = new;
	actual->prev = new;
	return (new);
}
