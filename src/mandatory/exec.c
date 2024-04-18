/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:44:49 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/17 17:23:48 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_start(t_node *node)
{

}

void	ft_init_exec(t_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE ||
		node->type == NODE_OR ||
		node->type == NODE_AND)
	{
		ft_init_exec(node->prev);
		// if (node->type == NODE_HERE_DOC)
		// 	ft_init_exec(node->next);
	}
	else
		ft_start(node);
}
