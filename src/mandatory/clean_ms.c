/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:30:19 by skapersk          #+#    #+#             */
/*   Updated: 2024/05/27 13:07:05 by skapersk         ###   ########.fr       */
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

void	ft_clean_nodes(t_node *node)
{
	t_node 		*tmp;
	t_red_node	*tmp_r;
	int			i;

	i = 0;
	tmp = node;
	node = node->next;
	if (convert(tmp->type) == NULL)
		return ;
	if (tmp->red_node != NULL && tmp->red_node->value != NULL)
	{
		tmp_r = tmp->red_node;
		while (tmp->red_node)
		{
			tmp->red_node = tmp->red_node->next;
			free(tmp_r->args);
			free(tmp_r->value);
			tmp_r = tmp->red_node;
		}
	}
	if (tmp->cmd != NULL)
		free(tmp->cmd);
	else if (tmp->sub_node != NULL)
		free(tmp->sub_node->args);
	if (tmp->left != NULL)
		free(tmp->left->value);
	if (tmp->rigth != NULL)
		free(tmp->rigth->value);
	if (tmp->c_cmd != NULL)
	{
		while ((tmp->c_cmd->expand)[i])
		{
			free((tmp->c_cmd->expand)[i]);
			i++;
		}
	}
	tmp = node;
}

void	ft_clear_parsing(t_node *nodes)
{
	if (nodes == NULL)
		return ;
	else
	{
		ft_clean_nodes(nodes);
		ft_clear_parsing(nodes->next);
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
}
