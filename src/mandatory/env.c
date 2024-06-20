/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:23:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/20 11:14:50 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_valid_name(char *name)
{
	int	i;

	i = 0;
	if (!name || (isalpha(name[0]) == FALSE && name[0] != '_'))
		return (FALSE);
	while (name[++i])
	{
		if (isalnum(name[i]) == FALSE && name[i] != '_')
			return (FALSE);
	}
	return (TRUE);
}

char	*catch_value(char *name, t_dblist *env)
{
	while (env)
	{
		if (ft_strncmp(name, (((t_variable *)(env->content))->name),
			ft_strlen(name)) == 0)
			break ;
		env = env->next;
	}
	return ((((t_variable *)(env->content))->value));
}

void	print_filled_variable(void *content)
{
	if (((t_variable *)content)->value
		&& ((t_variable *)content)->value[0])
	{
		print_variable(content);
	}
}

void	print_variable(void *content)
{
	ft_putstr_fd(((t_variable *)content)->name, 1);
	ft_putchar_fd('=', 1);
	ft_putstr_fd(((t_variable *)content)->value, 1);
	ft_putchar_fd('\n', 1);
}

t_dblist	*generate_env(char **envp)
{
	t_dblist	*my_env;
	t_dblist	*new;
	int			i;

	i = 0;
	my_env = NULL;
	if (envp[i])
		my_env = ft_dblstnew(create_variable(envp[i++]));
	if (my_env == NULL || my_env->content == NULL)
		return (free(my_env), NULL);
	while (envp[i])
	{
		new = ft_dblstnew(create_variable(envp[i]));
		if (new == NULL || new->content == NULL)
			return (ft_dblstclear(&my_env, destroy_variable), free(new), NULL);
		ft_dblstadd_back(&my_env, new);
		i++;
	}
	return (my_env);
}

int	do_env(t_node *node, t_dblist *my_env)
{
	if (nbr_of_args(node->c_cmd->expand) > 0)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}

	ft_dblst_iter(my_env, print_filled_variable);
	return (0);
	// Modifier pour afficher une erreur si argument
}
