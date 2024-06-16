// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   clean_parsing.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/12 12:30:19 by skapersk          #+#    #+#             */
// /*   Updated: 2024/06/16 14:33:56 by skapersk         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// void	ft_clear_token(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp != NULL)
// 	{
// 		token = token->next;
// 		free(tmp->value);
// 		free(tmp);
// 		tmp = token;
// 	}
// }

// void	ft_free_red_nodes(t_red_node *red_node)
// {
// 	t_red_node	*tmp_r;

// 	while (red_node)
// 	{
// 		tmp_r = red_node;
// 		red_node = red_node->next;
// 		if (tmp_r->value)
// 		{
// 			free(tmp_r->value);
// 			tmp_r->value = NULL; 
// 		}
// 		free(tmp_r);
// 	}
// }

// void	ft_free_c_cmd_expand(char **expand)
// {
// 	int	i;

// 	i = 0;
// 	if (expand)
// 	{
// 		while (expand[i])
// 		{
// 			free(expand[i]);
// 			i++;
// 		}
// 		free(expand);
// 	}
// }

// void	ft_clean_nodes(t_node *node)
// {
// 	t_node	*tmp;

// 	if (!node || (!convert(node->type) && node->sub == NULL))
// 		return ;
// 	tmp = node;
// 	if (tmp->red_node)
// 	{
// 		ft_free_red_nodes(tmp->red_node);
// 		 node->red_node = NULL; 
// 	}
// 	if (tmp->c_cmd)
// 	{
// 		ft_free_c_cmd_expand(tmp->c_cmd->expand);
// 		if (tmp->c_cmd->wildcard)
// 			free_wildcards(tmp->c_cmd->wildcard);
// 		free(tmp->c_cmd);
// 		node->c_cmd = NULL; 
// 	}
// 	if (tmp->cmd)
// 	{
// 		free(tmp->cmd);
// 		node->cmd = NULL; 
// 	}
// }

// void	ft_clear_parsing(t_node *nodes)
// {
// 	if (nodes == NULL)
// 		return ;
// 	else if (nodes->sub != NULL)
// 	{
// 		ft_clear_parsing(nodes->sub);
// 		ft_clean_nodes(nodes);
// 		ft_clear_parsing(nodes->next);
// 		// ft_clean_nodes(nodes);
// 		free(nodes);
// 	}
// 	else
// 	{
// 		ft_clean_nodes(nodes);
// 		ft_clear_parsing(nodes->next);
// 		free(nodes);
// 	}
// 	// NEED TO CLOSE HERE DOC FDS
// }

#include "../../include/minishell.h"

void	ft_clear_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		token = token->next;
		free(tmp->value);
		free(tmp);
		tmp = token;
	}
}

void	ft_free_red_nodes(t_red_node *red_node)
{
	t_red_node	*tmp_r;

	while (red_node)
	{
		tmp_r = red_node;
		red_node = red_node->next;
		if (tmp_r->value)
		{
			free(tmp_r->value);
			tmp_r->value = NULL;
		}
		free(tmp_r);
	}
}

void	ft_free_c_cmd_expand(char **expand)
{
	int	i;

	i = 0;
	if (expand)
	{
		while (expand[i])
		{
			free(expand[i]);
			i++;
		}
		free(expand);
	}
}

void	ft_clean_nodes(t_node *node)
{
	if (!node || (!convert(node->type) && node->sub == NULL))
		return ;

	if (node->red_node)
	{
		ft_free_red_nodes(node->red_node);
		node->red_node = NULL;
	}
	if (node->c_cmd)
	{
		ft_free_c_cmd_expand(node->c_cmd->expand);
		if (node->c_cmd->wildcard)
			free_wildcards(node->c_cmd->wildcard);
		free(node->c_cmd);
		node->c_cmd = NULL;
	}
	if (node->cmd)
	{
		free(node->cmd);
		node->cmd = NULL;
	}
}

void	ft_clear_parsing(t_node *nodes)
{
	if (nodes == NULL)
		return;

	// Traiter d'abord les sous-nœuds
	if (nodes->sub != NULL)
	{
		ft_clear_parsing(nodes->sub);
		nodes->sub = NULL;
	}

	// Nettoyer le nœud courant
	ft_clean_nodes(nodes);

	// Passer au nœud suivant
	if (nodes->next != NULL)
	{
		t_node *next_node = nodes->next;
		nodes->next = NULL;
		ft_clear_parsing(next_node);
	}

	// Libérer le nœud courant
	free(nodes);
}
