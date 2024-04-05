/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:24:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*node;

// 	char	str[] = "Bonjour";
// 	node = NULL;
// 	node = ft_lstnew((void *)str);
// 	printf("The return value is %p.\n", node);
// 	printf("The content value is %s.\n", (char *)node->content);
// 	printf("The next value is %p.\n", node->next);
// 	free(node);
// 	return (0);
// }
