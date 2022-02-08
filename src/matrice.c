/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:09:43 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/08 19:49:34 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_splitter(char *str, char **splitter)
{
	int		i;

	i = 0;
	while (splitter[i])
	{
		if (ft_strcmp(str, splitter[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	get_value_i(char **matrice, char **splitter)
{
	int	i;

	i = 0;
	if (matrice[0] && is_splitter(matrice[i], splitter))
	{
		while (matrice[i] && is_splitter(matrice[i], splitter))
			i++;
		while (matrice[i] && !is_splitter(matrice[i], splitter))
			i++;
		while (matrice[i] && is_splitter(matrice[i], splitter))
			i++;
	}
	return (i);
}

char	**get_value_to_return(char **matrice, char **splitter, int i, int x)
{
	char	**to_return;
	int		y;

	y = 0;
	to_return = malloc(sizeof(char **)
			* (find_index_matrice(matrice, splitter) + 10));
	while (matrice[i])
	{
		x = 0;
		while (splitter[x])
		{
			if (ft_strcmp(matrice[i], splitter[x]) == 0)
			{
				to_return[y] = 0;
				return (to_return);
			}
			x++;
		}
		to_return[y] = get_unq_copy(matrice[i]);
		i++;
		y++;
	}
	to_return[y] = 0;
	return (to_return);
}

char	**ft_matrice_split(char **matrice, char **splitter)
{
	int		i;
	char	**to_return;
	int		x;

	x = 0;
	i = get_value_i(matrice, splitter);
	to_return = get_value_to_return(matrice, splitter, i, x);
	return (to_return);
}

void	clean_two_matrice(char **m1, char **m2)
{
	free_that_matrice(m1);
	free_that_matrice(m2);
}
