/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:09:43 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 23:02:16 by sserbin          ###   ########.fr       */
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

int	find_index_matrice(char **matrice, char *to_find)
{
	unsigned int	i;

	i = 0;
	if (!matrice || !to_find)
		return (-1);
	while (matrice[i])
	{
		if (ft_strcmp(matrice[i], to_find) == 0)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_matrice_split(char **matrice, char *splitter)
{
	int		i;
	char	**to_return;

	i = 0;
	to_return = malloc(sizeof(char **)
			* (find_index_matrice(matrice, splitter) + 1));
	while (matrice[i])
	{
		if (ft_strcmp(matrice[i], splitter) == 0)
			break ;
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
