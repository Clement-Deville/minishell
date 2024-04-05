/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstfirst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:48:54 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:05 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

t_dblist	*ft_dblstfirst(void *content)
{
	t_dblist	*node;

	node = (t_dblist *)malloc(sizeof(t_dblist));
	if (!node)
		return (NULL);
	node->content = content;
	node->prev = node;
	node->next = node;
	return (node);
}
