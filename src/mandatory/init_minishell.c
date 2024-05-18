/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:37:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/18 13:48:48 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_mini_env	*get_ms(void)
{
	static t_mini_env	minishell;

	return (&minishell);
}

void	ft_init_env(char **env, char *line)
{
	ft_memset(get_ms(), 0, sizeof(t_mini_env));
	if (env == NULL)
	{
		ft_printf("Erreur : pointeur de variable d'environnement nul\n");
		return ;
	}
	get_ms()->env = env;
	get_ms()->envlst = generate_env(env);
	if (line == NULL)
	{
		ft_printf("Erreur : pointeur de ligne de commande nul\n");
		return ;
	}
	get_ms()->line = line;
}
