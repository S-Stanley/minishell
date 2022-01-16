/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coop <coop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:55:12 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 00:48:58 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	if (n > 0)
	{
		ptr = s;
		while (n > 0)
		{
			*(ptr++) = 0;
			n--;
		}
	}
}
