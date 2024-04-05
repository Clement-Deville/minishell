/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:00:16 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include "stdio.h"

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*new;

// 	head = ft_lstnew("world");
// 	new = ft_lstnew("Hello ");
// 	ft_lstadd_front(0, new);
// 	printf("New head content is: \"%p\".\n", head->content);
// 	printf("New head next content is: \"%p\".\n", head->next->content);
// 	return (0);
// }
