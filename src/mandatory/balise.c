/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balise.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:52:20 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/21 10:52:44 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clean_balise(void)
{
	if (get_ms()->balise)
	{
		free(get_ms()->balise);
		get_ms()->balise = NULL;
	}
}

char	*set_color(void)
{
	char	color[10];
	char	*balise;

	if (get_ms()->exit)
		ft_strlcpy(color, "\001\033[1;31m\002", 10);
	else
		ft_strlcpy(color, "\001\033[0;32m\002", 10);
	balise = ft_strjoin(color, "➜  \001\033[1;36m\002");
	return (balise);
}

char	*get_balise(void)
{
	char	*current_dir_name;
	char	*tmp;
	char	*balise;

	clean_balise();
	current_dir_name = getcwd(NULL, 0);
	if (current_dir_name == NULL)
		return (perror("getcwd"), NULL);
	balise = set_color();
	if (balise == NULL)
		return (perror("Malloc"), free(current_dir_name), NULL);
	tmp = balise;
	balise = ft_strjoin(balise, current_dir_name);
	if (balise == NULL)
		return (perror("Malloc"), free(current_dir_name), free(tmp), NULL);
	free(tmp);
	tmp = balise;
	balise = ft_strjoin(balise, " \001\033[0m\002");
	if (balise == NULL)
		return (perror("Malloc"), free(current_dir_name), free(tmp), NULL);
	return (free(current_dir_name), balise);
}
