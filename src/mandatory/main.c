/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/24 11:58:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			ft_printf("------ %p ------\n", node);
			ft_printf("%s with ", convert2(node->red_node->type));
			ft_printf("%s \n", node->red_node->value);
			node->red_node = node->red_node->next;
		}
	}
	if (node->cmd != NULL)
		ft_printf("Command: %s\n", node->cmd);
	else if (node->sub != NULL)
	{
		ft_printf("----- %p -----\n", node);
		ft_printf("Subshell: ");
		ft_printf("----- sub : %p -----\n", node->sub);

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

void	do_readline(void)
{
	if (get_ms()->line)
	{
		free(get_ms()->line);
		get_ms()->line = NULL;
	}
	if (get_ms()->exit == 130 && get_ms()->signal)
	{
		get_ms()->signal = FALSE;
		ft_printf("\n");
	}
	if (get_ms()->exit == 131 && get_ms()->signal)
	{
		get_ms()->signal = FALSE;
		ft_printf("Quit (core dumped)\n");
	}
	// Need
	get_ms()->balise = get_balise();
	if (get_ms()->balise)
		get_ms()->line = readline(get_ms()->balise);
	else if (get_ms()->exit)
		get_ms()->line = readline("\001\033[1;31m\002➜ \001\033[0m\002");
	else
		get_ms()->line = readline("\001\033[1;32m\002➜ \001\033[0m\002");
	if (get_ms()->line == NULL)
	{
		ft_putendl_fd("exit", 2);
		ft_clear_envlst(get_ms());
		exit (get_ms()->exit);
	}
}

int	init_minishell(void)
{
	t_mini_env	*ms;

	ms = get_ms();
	ms->parent = TRUE;
	while (1)
	{
		do_readline();
		if (get_ms()->line[0])
			add_history(get_ms()->line);
		if (!ft_tokenization(ms))
		{
			ft_handle_parse_err(ms);
			ft_clear_token(ms->tokens);
			continue ;
		}
		init_parsing(ms);
		if (get_ms()->err.str)
		{
			get_ms()->f_or_nf = 1;
			ft_handle_parse_err(ms);
			continue ;
		}
		// exec_parse(ms->nodes);
		if (exec_here_doc(ms->nodes))
		{
			get_ms()->f_or_nf = 0;
			continue ;
		}
		start_exec(ms->nodes, &(ms->envlst));
		if (get_ms()->f_or_nf == 0)
		{
			ft_garbage(NULL, TRUE);
			ft_clear_token(get_ms()->tokens);
			ft_clear_parsing(get_ms()->nodes);
		}
		else
		{
			ft_garbage(NULL, TRUE);
			ft_clear_parsing(get_ms()->nodes);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	returned_val;

	returned_val = 0;
	(void)ac;
	(void)av;
	setup_signals();
	ft_init_env(env);
	init_minishell();
	returned_val = get_ms()->exit;
	ft_clean_ms();
	return (returned_val);
}
