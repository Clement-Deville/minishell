/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstadd_after.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:07:45 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:05 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

t_dblist	*ft_dblstadd_after(t_dblist *actual, t_dblist *new)
{
	if (!actual || !new)
		return (NULL);
	new->prev = actual;
	new->next = actual->next;
	if (actual->next)
		actual->next->prev = new;
	actual->next = new;
	return (new);
}
