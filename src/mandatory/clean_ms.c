/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:30:19 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/28 13:59:40 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_clear_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp != NULL)
	{
		token = token->next;
		free(tmp->value);
		free(tmp);
		tmp = token;
	}
}

void ft_clean_nodes(t_node *node) {
    t_node *tmp;
    t_red_node *tmp_r;
    int i;

    i = 0;
    tmp = node;
    if (convert(tmp->type) == NULL || node == NULL)
        return;
    if (tmp->red_node != NULL && tmp->red_node->value != NULL) {
        tmp_r = tmp->red_node;
        while (tmp->red_node) {
            tmp->red_node = tmp->red_node->next;
            // if (tmp_r->args != NULL) { // Ajout de vérification de nullité
            //     free(tmp_r->args);
            //     tmp_r->args = NULL; // Optionnel : éviter les double free
            // }
            if (tmp_r->value != NULL) { // Ajout de vérification de nullité
                free(tmp_r->value);
                tmp_r->value = NULL; // Optionnel : éviter les double free
            }
            tmp_r = tmp->red_node;
        }
    } else if (tmp->sub_node != NULL && tmp->sub_node->args != NULL) {
        free(tmp->sub_node->args);
        tmp->sub_node->args = NULL; // Optionnel : éviter les double free
    }
    if (tmp->c_cmd != NULL) {
        while (tmp->c_cmd->expand && (tmp->c_cmd->expand)[i]) {
            free((tmp->c_cmd->expand)[i]);
            (tmp->c_cmd->expand)[i] = NULL; // Optionnel : éviter les double free
            i++;
        }
    }
    if (tmp->red_node) {
        free(tmp->red_node);
        tmp->red_node = NULL; // Optionnel : éviter les double free
    }
    if (tmp->sub_node) {
        free(tmp->sub_node);
        tmp->sub_node = NULL; // Optionnel : éviter les double free
    }
    if (tmp->cmd) {
        free(tmp->cmd);
        tmp->cmd = NULL; // Optionnel : éviter les double free
    }
}

void	ft_clear_parsing(t_node *nodes)
{
	if (nodes == NULL)
		return ;
	else
	{
		ft_clean_nodes(nodes);
		ft_clear_parsing(nodes->next);
		// free(nodes);
	}
}

void	ft_clear_envlst(t_mini_env *mini_s)
{
	int	i;

	i = 0;
	if (mini_s->env)
	{
		while (mini_s->env[i])
		{
			free(mini_s->env[i]);
			i++;
		}
	}
	free(mini_s);
}

void	ft_clean_ms(void)
{
	ft_garbage(NULL, TRUE);
	ft_clear_token(get_ms()->tokens);
	ft_clear_parsing(get_ms()->nodes);
	get_ms()->nodes = NULL;
}
