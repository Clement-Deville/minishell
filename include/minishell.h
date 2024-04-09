/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/09 11:00:11 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>

typedef struct s_env
{
	char	*value;
	t_bool	export;
}	t_env;

// BUILT-IN COMMANDS

int			do_echo(char *str, t_bool nonewline);
int			do_pwd(void);
int			do_env(t_dblist *env);

// ENV

t_dblist	*generate_env(char **envp);

// UTILS

void		print_env(void *content);

#endif
