/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:56:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/08 13:15:04 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_pwd(void)
{
	char	*current_dir_name;

	current_dir_name = getcwd(NULL, 0);
	if (current_dir_name == NULL)
		return (perror("Pwd error:"), 1);
	ft_putstr_fd(current_dir_name, 1);
	ft_putchar_fd('\n', 1);
	free(current_dir_name);
	return (0);
}
