/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:33:35 by skapersk          #+#    #+#             */
/*   Updated: 2024/06/24 15:33:55 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*convert(t_node_type type)
{
	if (type == NODE_AND)
		return ("NODE AND");
	else if (type == NODE_OR)
		return ("NODE OR");
	else if (type == NODE_PIPE)
		return ("NODE PIPE");
	else if (type == NODE_CMD)
		return ("NODE_CMD");
	else
		return (NULL);
}
