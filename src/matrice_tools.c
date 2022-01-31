/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:09:45 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 02:32:43 by sserbin          ###   ########.fr       */
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

bool	find_string_in_matrice(char *to_find, char **matrice)
{
	unsigned int	i;
	char			**var;

	i = 0;
	if (!to_find || !matrice)
		return (false);
	while (matrice[i])
	{
		var = ft_split(to_find, '=');
		if (ft_strcmp(var[0], matrice[i]) == 0)
		{
			free_that_matrice(var);
			return (true);
		}
		free_that_matrice(var);
		i++;
	}
	return (false);
}
