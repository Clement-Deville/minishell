/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:22:18 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:49:16 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	ft_dblstclear(t_dblist **lst, void (*del)(void*))
{
	t_dblist	*next;
	t_dblist	*actual;

	if (!del || !lst || !*lst)
		return ;
	actual = *lst;
	while (actual)
	{
		next = actual->next;
		ft_dblstdelone(actual, del);
		actual = next;
	}
	*lst = NULL;
	return ;
}
