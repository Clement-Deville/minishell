/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:37:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/04/08 15:23:25 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_init_env(char **env, t_mini_env *ms, char *line) 
{
    ft_memset(ms, 0, sizeof(t_mini_env));
    if (env == NULL) {
        ft_printf("Erreur : pointeur de variable d'environnement nul\n");
        return ;
    }
    ms->env = env;
    if (line == NULL) {
        ft_printf("Erreur : pointeur de ligne de commande nul\n");
        return ;
    }
    ms->line = line;
}
