/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/15 16:04:48 by skapersk         ###   ########.fr       */
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

int	main_subshell(int ac, char *av, char **env)
{
	// t_mini_env    *ms;
	char	*line;
	int		status;

	line = malloc(sizeof(char) + ac + 2);
	ft_strlcpy(line,av, ac + 1);
	ft_init_env(env);
	get_ms()->line = line;
	ft_tokenization(get_ms());
	init_parsing(get_ms());
	status = start_exec(get_ms()->nodes, &(get_ms()->envlst));
	free(line);
	return (status);
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

char	*get_balise(void)
{
	// ft_printf("\r");
	// ft_printf("\033[K");
	char	*current_dir_name;
	char	color[8];
	char	*balise;
	char	*tmp;

	if (get_ms()->balise)
	{
		free(get_ms()->balise);
		get_ms()->balise = NULL;
	}
	current_dir_name = getcwd(NULL, 0);
	if (get_ms()->exit)
		ft_strlcpy(color, "\e[1;31m", 9);
	else
		ft_strlcpy(color, "\e[0;32m", 9);
	// ft_printf("%s\u2192  \e[1;36m%s \e[0m", color, current_dir_name);
	balise = ft_strjoin(color, "\u2192  \001\033[1;36m");
	if (balise)
	{
		tmp = balise;
		balise = ft_strjoin(balise, current_dir_name);
		free(tmp);
		tmp = balise;
		balise = ft_strjoin(balise, " \e[0m");
		free (tmp);
	}
	if (current_dir_name)
		free(current_dir_name);
	return (balise);
}

// void	ft_heredoc_go_expand(t_node *node)
// {
// 	char	*line;
// 	int		tmp_fd;

// 	if (node == NULL)
// 		fprintf(stderr, "YOLO\n");
// 	if (node->red_node != NULL && node->red_node->value != NULL)
// 	{
// 		if (node->red_node->type == NODE_HERE_DOC)
// 		{
// 			tmp_fd = open("/tmp/heredoc_expanded.tmp",
// 					O_RDWR | O_CREAT | O_TRUNC, 0644);
// 			if (tmp_fd < 0)
// 			{
// 				perror("open");
// 				return ;
// 			}
// 			line = get_next_line(node->red_node->here_doc);
// 			while (line)
// 			{
// 				ft_heredoc_expand(line, tmp_fd);
// 				free(line);
// 				line = get_next_line(node->red_node->here_doc);
// 			}
// 			// close(node->red_node->here_doc);
// 			node->red_node->here_doc = tmp_fd;
// 		}
// 	}
// }

void	ft_heredoc_go_expand(t_node *node)
{
	int		tmp_fd;
	char	*line;
	char	buffer[1024];
	ssize_t	bytes_read;
	char	*quotes;

	quotes = node->red_node->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	if (*quotes)
		return ;
	if (node->red_node->here_doc < 0)
	{
		perror("open");
		return ;
	}
	tmp_fd = open("/tmp/tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		perror("open");
		close(node->red_node->here_doc);
		return ;
	}
	while ((line = get_next_line(node->red_node->here_doc)) != NULL)
	{
		ft_heredoc_expand(line, tmp_fd);
		free(line);
	}
	close(node->red_node->here_doc);
	close(tmp_fd);
	tmp_fd = open("/tmp/tmp_heredoc", O_RDONLY);
	if (tmp_fd < 0)
	{
		perror("open");
		return ;
	}
	int new_fd = open("/tmp/final_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd < 0)
	{
		perror("open");
		close(tmp_fd);
		return ;
	}
	while ((bytes_read = read(tmp_fd, buffer, sizeof(buffer))) > 0)
	{
		if (write(new_fd, buffer, bytes_read) != bytes_read)
		{
			perror("write");
			close(new_fd);
			close(tmp_fd);
			return ;
		}
	}
	if (bytes_read < 0)
	{
		perror("read");
	}
	close(new_fd);
	close(tmp_fd);
	node->red_node->here_doc = open("/tmp/final_heredoc", O_RDONLY);
	if (node->red_node->here_doc < 0)
	{
		perror("open");
		return ;
	}
}

void	exec_test(t_node *nodes)
{
	t_node	*tmp;

	tmp = nodes;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		if (tmp->red_node != NULL)
			ft_init_heredoc(tmp);
		else if (tmp->sub != NULL)
			exec_test(tmp->sub);
		dodge_cmd(&tmp);
	}
}

int	init_minishell(void)
{
	t_mini_env	*ms;

	ms = get_ms();
	ms->parent = TRUE;
	while (1)
	{
		if (get_ms()->line)
		{
			free(get_ms()->line);
			get_ms()->line = NULL;
		}
		get_ms()->balise = get_balise();
		if (get_ms()->balise)
			get_ms()->line = readline(get_ms()->balise);
		else if (get_ms()->exit)
			get_ms()->line = readline("\e[1;31m\u2192 \e[0m");
		else
			get_ms()->line = readline("\e[1;32m\u2192 \e[0m");
		// free(balise);
		// if (line == NULL)
		// {
		// 	ft_printf("Erreur : pointeur de ligne de commande nul\n");
		// 	return (0);
		// }
		if (get_ms()->line == NULL)
		{
			ft_putendl_fd("exit", 2);
			exit (get_ms()->exit);
		}
		else if (get_ms()->line[0])
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
		exec_test(ms->nodes);
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
	ft_init_env(env);
	setup_signals();
	init_minishell();
	returned_val = get_ms()->exit;
	ft_clean_ms();
	return (returned_val);
}


// int	main(int ac, char **av, char **env)
// {
// 	t_mini_env	*ms;
// 	char		*line;
// 	int			last_exit;
// 	int			status;

// 	(void)ac;
// 	(void)av;
// 	status = 0;
// 	ms = get_ms();
// 	last_exit = 0;
// 	ft_init_env(env);
// 	setup_signals();
// 	while (1)
// 	{
// 		print_balise(last_exit);
// 		line = get_next_line(0);
// 		if (line == NULL)
// 		{
// 			ft_printf("Erreur : pointeur de ligne de commande nul\n");
// 			return (0);
// 		}
// 		get_ms()->exit = last_exit;
// 		get_ms()->line = line;
// 		if (!ft_strncmp("stop\n", line, ft_strlen(line)))
// 			break ;
// 		ft_tokenization(ms);
// 		ms->nodes = init_parsing(ms);
// 		start_exec(ms->nodes, &(ms->envlst));
// 		last_exit = get_ms()->exit;
// 	}
// 	free(line);
// 	ft_clean_ms();
// 	return (last_exit);
// }
