/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:09:43 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/22 15:48:20 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_len_matrice(char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return (0);
	while (matrice[i])
		i++;
	return (i);
}

void	read_that_matrice(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
	{
		printf("%s\n", matrice[i]);
		i++;
	}
}

int	find_index_matrice(char **matrice, char **to_find)
{
	unsigned int	i;
	unsigned int	x;

	i = 0;
	if (!matrice || !to_find)
		return (-1);
	while (matrice[i])
	{
		x = 0;
		while (to_find[x])
		{
			if (ft_strcmp(matrice[i], to_find[x]) == 0)
				return (i);
			x++;
		}
		i++;
	}
	return (i);
}

char	**ft_matrice_split(char **matrice, char **splitter)
{
	int		i;
	char	**to_return;
	int		x;

	i = 0;
	to_return = malloc(sizeof(char **)
			* (find_index_matrice(matrice, splitter) + 1));
	while (matrice[i])
	{
		x = 0;
		while (splitter[x])
		{
			if (ft_strcmp(matrice[i], splitter[x]) == 0)
			{
				to_return[i] = 0;
				return (to_return);
			}
			x++;
		}
		to_return[i] = matrice[i];
		i++;
	}
	to_return[i] = 0;
	return (to_return);
}

int	count_len_matrice(char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return (0);
	while (matrice[i])
		i++;
	return (i);
}
