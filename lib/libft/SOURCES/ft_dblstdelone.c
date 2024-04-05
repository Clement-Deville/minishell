/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:34:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	ft_dblstdelone(t_dblist *dblst, void (*del)(void*))
{
	if (!dblst || !del)
		return ;
	del(dblst->content);
	free(dblst);
	dblst = NULL;
}
