/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:49:38 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	i;
// 	t_list	*node;
// 	int	value;

// 	i = 0;
// 	value = 10;
// 	node = ft_lstnew(&value);
// 	printf("%d\n", *(int *)node->content);
// 	while(i < 3)
// 	{
// 		ft_lstadd_front(&node, ft_lstnew(&i));
// 		printf("%d\n", *(int *)node->content);
// 		i++;
// 	}
// 	printf("Content of last element of the
//	linked list is: %d\n", *(int *)ft_lstlast(node)->content);
// 	return (0);
// }
