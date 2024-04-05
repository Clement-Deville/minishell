/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:39:52 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*actual;
	int		count;

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

// #include <stdio.h>

// int	main(void)
// {
// 	int	i;
// 	t_list	*node;

// 	i = 0;
// 	node = ft_lstnew(&i);
// 	printf("%d\n", *(int *)node->content);
// 	while(i < 7)
// 	{
// 		ft_lstadd_front(&node, ft_lstnew(&i));
// 		printf("%d\n", *(int *)node->content);
// 		i++;
// 	}
// 	printf("Size of linked list is: %d\n", ft_lstsize(node));
// 	return (0);
// }
