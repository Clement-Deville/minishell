/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:56:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/14 11:38:02 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_pwd(t_node *node)
{
	char	*current_dir_name;

	current_dir_name = getcwd(NULL, 0);
	if (current_dir_name == NULL)
	{
		if (node->silent == FALSE)
			perror("Pwd error");
		return (1);
	}
	ft_putstr_fd(current_dir_name, 1);
	ft_putchar_fd('\n', 1);
	free(current_dir_name);
	return (0);
}
