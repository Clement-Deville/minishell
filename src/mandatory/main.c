/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/05/20 14:09:51 by skapersk         ###   ########.fr       */
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

int	main_subshell(int ac, char **av, char **env)
{
	t_mini_env	*ms;
	char		*line;
	t_token		*tmp_token;
	int			i;

	i = 0;
	line = malloc(sizeof(char) + ac + 2);
	ft_strlcpy(line, *av, ac + 1);
	while (line[i])
		i++;
	line[i] = '\n';
	i++;
	line[i] = '\0';
	ms = get_ms();
	ft_init_env(env, line);
	ft_tokenization(ms);
	ms->nodes = init_parsing(ms);
	start_exec(ms->nodes, ms);
	free(line);
	while (ms->tokens != NULL)
	{
		tmp_token = ms->tokens;
		ms->tokens = ms->tokens->next;
		free(tmp_token->value);
		free(tmp_token);
	}
	return (ms->exit);
}

int	main(int ac, char **av, char **env)
{
	t_mini_env	*ms;
	char		*line;
	t_token		*tmp_token;

	(void)ac;
	(void)av;
	ms = get_ms();
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp("exit\n", line, ft_strlen(line)))
			break ;
		ft_init_env(env, line);
		ft_tokenization(ms);
		ms->nodes = init_parsing(ms);
		start_exec(ms->nodes, ms);
	}
	free(line);
	while (ms->tokens != NULL)
	{
		tmp_token = ms->tokens;
		ms->tokens = ms->tokens->next;
		free(tmp_token->value);
		free(tmp_token);
	}
	return (0);
}
