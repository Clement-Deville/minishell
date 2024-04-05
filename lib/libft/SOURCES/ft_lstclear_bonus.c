/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 05:58:13 by erik              #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*actual;

	if (!del || !lst || !*lst)
		return ;
	actual = *lst;
	while (actual)
	{
		next = actual->next;
		ft_lstdelone(actual, del);
		actual = next;
	}
	*lst = NULL;
	return ;
}
