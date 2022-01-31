/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_that_matrice.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:17:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 21:13:56 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_that_matrice(char **matrice)
{
	unsigned int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		if (matrice[i])
			free(matrice[i]);
		i++;
	}
	free(matrice);
}
