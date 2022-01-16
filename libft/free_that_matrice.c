/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_that_matrice.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:17:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/16 19:26:13 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_that_matrice(char **matrice)
{
	unsigned int	i;

	i = 0;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}
