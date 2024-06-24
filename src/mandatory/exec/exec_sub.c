/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:35:48 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 16:06:59 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_sub(t_node *node, t_dblist **env)
{
	int		pid;
	int		red_status;
	t_node	*subnode;

	subnode = node->sub;
	pid = fork();
	if (pid < 0)
		return (perror("Fork"), ENO_CRITICAL);
	if (pid == 0)
	{
		red_status = do_redirections(node);
		if (red_status == -1)
			exit(clean_and_exit (ENO_CRITICAL));
		if (red_status)
			exit(clean_and_exit (1));
		get_ms()->parent = FALSE;
		exit(clean_and_exit(start_exec(subnode, env)));
	}
	get_ms()->exit = do_wait(pid);
	if (get_ms()->exit == -1)
		return (ENO_CRITICAL);
	return (get_ms()->exit);
	// Need to leave program properly
}
