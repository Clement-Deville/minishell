/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_htab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:13:07 by cdeville          #+#    #+#             */
/*   Updated: 2024/02/20 17:23:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/libft.h"

void	print_htab(t_hash *htab, int size)
{
	int		i;
	int		color;
	t_hash	*actual;

	i = 0;
	while (i < size)
	{
		color = 0;
		if (htab[i].content == NULL)
			ft_printf("\t%i\t===>\t\n", i);
		else
		{
			actual = &htab[i];
			ft_printf("\t%i", i);
			while (actual)
			{
				ft_printf("\033[0;3%im\t===>\t", (color % 6) + 1);
				ft_printf("%s", actual->content);
				actual = actual->next;
				color++;
			}
			ft_printf("\033[0;37m\n");
		}
		i++;
	}
}

void	print_efficiency(t_hash *htab, int size)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (size == 0 || htab == NULL)
		return ;
	while (i < size)
	{
		if (htab[i].content == NULL)
			count++;
		i++;
	}
	ft_printf("The effiency of that hash table is ");
	ft_printf("%d%%\n", (size - count) * 100 / size);
}
