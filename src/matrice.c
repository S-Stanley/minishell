/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:09:43 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 19:29:47 by sserbin          ###   ########.fr       */
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
