/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:10:54 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	return ;
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	i;
// 	t_list	*node;
// 	t_list	*last;
// 	int	value;
// 	int	lastvalue;

// 	i = 0;
// 	value = 10;
// 	lastvalue = 100;
// 	node = ft_lstnew(&value);
// 	printf("%d\n", *(int *)node->content);
// 	while (i < 3)
// 	{
// 		ft_lstadd_front(&node, ft_lstnew(&i));
// 		printf("%d\n", *(int *)node->content);
// 		i++;
// 	}
// 	printf("Content of last element of the linked list is: %d\n",
// *(int *)ft_lstlast(node)->content);
// 	printf("Size of linked list is: %d\n", ft_lstsize(node));
// 	last = ft_lstnew(&lastvalue);
// 	ft_lstadd_back(&node, last);
// 	printf("Now it is: %d\n", *(int *)ft_lstlast(node)->content);
// 	printf("And size is: %d\n", ft_lstsize(node));
// 	return (0);
// }
