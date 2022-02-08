/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_that_matrice.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:17:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/08 19:52:48 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	free_that_matrice(char **matrice)
{
	unsigned int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}
