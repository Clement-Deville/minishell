/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:57:59 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*actual;

	if (!lst || !del || !f)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (!head)
		return (NULL);
	actual = head;
	lst = lst->next;
	while (lst)
	{
		actual->next = ft_lstnew(f(lst->content));
		if (!actual->next)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
		actual = actual->next;
	}
	actual->next = NULL;
	return (head);
}

// void * addOne(void * p) {void * r = malloc(sizeof(int));
// *(int*)r = *(int*)p + 1; return (r);}

// int	main(void)
// {
// 	int tab[] = {0, 1, 2, 3};
// 	t_list * l =  ft_lstnew(tab);
// 	for (int i = 1; i < 4; ++i)
// 		ft_lstadd_back(&l, ft_lstnew(tab + i));
// 	t_list * m = ft_lstmap(l, addOne, free);
// 	t_list * tmp = l;
// 	/* 1 2 3 4 */ for (int i = 0; i < 4; ++i)
// 	{
// 		tmp = (t_list *)tmp->next;
// 	}
// 	tmp = m;
// 	/* 5 6 7 8 */ for (int i = 0; i < 4; ++i)
// 	{
// 		tmp = (t_list *)tmp->next;
// 	}
// 	return (0);
// }
