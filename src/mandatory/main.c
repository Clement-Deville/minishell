/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/28 15:52:33 by cdeville         ###   ########.fr       */
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

void	do_node(t_node *node)
{
	if (convert(node->type) != NULL)
		ft_printf("TYPE NODE : %s --> ", convert(node->type));
	if (node->red_node != NULL && node->red_node->value != NULL)
	{
		// ft_printf("%s with ", convert2(node->red_node->type));
		// ft_printf("%s ", node->red_node->value);
		while (node->red_node)
		{
			ft_printf("%s with ", convert2(node->red_node->type));
			ft_printf("%s \n", node->red_node->value);
			node->red_node = node->red_node->next;
		}
	}
	if (node->cmd != NULL)
		ft_printf("Command: %s\n", node->cmd);
	else if (node->sub_node != NULL)
		ft_printf("Subshell: %s\n", node->sub_node->args);
	if (node->left != NULL)
		ft_printf("LEFT : %s\n", node->left->value);
	if (node->rigth != NULL)
		ft_printf("RIGHT : %s\n", node->rigth->value);
}

void	exec_parse(t_node *node)
{
	if (node == NULL)
		return ;
	else
	{
		do_node(node);
		exec_parse(node->next);
	}
}

int	main_subshell(int ac, char *av, char **env)
{
	// t_mini_env    *ms;
	char        *line;
	int            i;

	i = 0;
	line = malloc(sizeof(char) + ac + 2);
	ft_strlcpy(line,av, ac + 1);
	ft_init_env(env);
	get_ms()->line = line;
	ft_tokenization(get_ms());
	init_parsing(get_ms());
	start_exec(get_ms()->nodes, &(get_ms()->envlst));
	free(line);
	return (get_ms()->exit);
}

// int	main_subshell(int ac, char **av, char **env)
// {
// 	t_mini_env	*ms;
// 	char		*line;
// 	t_token		*tmp_token;

// 	ms = NULL;
// 	line = malloc(sizeof(char) + ac + 2);
// 	ft_strlcpy(line, *av, ac + 1);
// 	ft_init_env(env);
// 	 get_ms()->line = line;
// 	// L'environement ne doit il pas etre herite du parent?
// 	ft_tokenization(get_ms());
// 	init_parsing(ms);
// 	start_exec(ms->nodes, &(ms->envlst));
// 	free(line);
// 	while (ms->tokens != NULL)
// 	{
// 		tmp_token = ms->tokens;
// 		ms->tokens = ms->tokens->next;
// 		free(tmp_token->value);
// 		free(tmp_token);
// 	}
// 	return (ms->exit);
// }

int	main(int ac, char **av, char **env)
{
	t_mini_env	*ms;
	char		*line;
	int			last_exit;
	int			status;

	(void)ac;
	(void)av;
	status = 0;
	ms = get_ms();
	last_exit = 0;
	ft_init_env(env);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
		{
			ft_printf("Erreur : pointeur de ligne de commande nul\n");
			return (0);
		}
		get_ms()->exit = last_exit;
		get_ms()->line = line;
		if (!ft_strncmp("stop\n", line, ft_strlen(line)))
			break ;
		ft_tokenization(ms);
		ms->nodes = init_parsing(ms);
		start_exec(ms->nodes, &(ms->envlst));
		last_exit = get_ms()->exit;
	}
	free(line);
	ft_clean_ms();
	return (last_exit);
}
