/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/31 17:59:38 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

char	*convert2(t_red_type type)
{
	if (type == NODE_RED_IN)
		return ("NODE_RED_IN");
	else if (type == NODE_RED_OUT)
		return ("NODE_RED_OUT");
	else if (type == NODE_APPEND)
		return ("NODE_APPEND");
	else if (type == NODE_HERE_DOC)
		return ("NODE_HERE_DOC");
	else
		return (NULL);
}

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

void	exec_parse(t_node *node);

void	do_node(t_node *node)
{
	if (convert(node->type) != NULL && node->sub == NULL )
		ft_printf("TYPE NODE : %s --> ", convert(node->type));
	if (node->red_node != NULL && node->red_node->value != NULL)
	{
		while (node->red_node)
		{
			ft_printf("%s with ", convert2(node->red_node->type));
			ft_printf("%s \n", node->red_node->value);
			node->red_node = node->red_node->next;
		}
	}
	if (node->cmd != NULL)
		ft_printf("Command: %s\n", node->cmd);
	else if (node->sub != NULL)
	{
		ft_printf("Subshell: ");
		exec_parse(node->sub);
	}
	if (node->left != NULL)
		ft_printf("LEFT : %s\n", node->left->value);
	if (node->rigth != NULL)
		ft_printf("RIGHT : %s\n", node->rigth->value);
}

void	exec_parse(t_node *node)
{
	if (!node)
		return ;
	else
	{
		do_node(node);
		exec_parse(node->next);
	}
}

int	main_subshell(int ac, char **av, char **env)
{
	char		*line;

	line = malloc(sizeof(char) + ac + 2);
	ft_strlcpy(line, *av, ac + 1);
	ft_init_env(env);
	get_ms()->line = line;
	ft_tokenization(get_ms());
	init_parsing(get_ms());
	start_exec(get_ms()->nodes, get_ms());
	free(line);
	return (get_ms()->exit);
}

int	main(int ac, char **av, char **env)
{
	int		last_exit;

	(void)ac;
	(void)av;
	last_exit = 0;
	ft_init_env(env);
	while (1)
	{
		get_ms()->line = get_next_line(0);
		if (get_ms()->line == NULL)
		{
			ft_printf("Erreur : pointeur de ligne de commande nul\n");
			return (0);
		}
		get_ms()->exit = last_exit;
		if (!ft_strncmp("stop\n", get_ms()->line, ft_strlen(get_ms()->line)))
			break ;
		ft_tokenization(get_ms());
		init_parsing(get_ms());
		// exec_parse(get_ms()->nodes);
		// start_exec(get_ms()->nodes, get_ms());
		// last_exit = get_ms()->exit;
		// ft_clean_ms();
		free(get_ms()->line);
	}
	free(get_ms()->line);
	ft_clear_envlst(get_ms());
	return (last_exit);
}
