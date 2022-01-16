/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:28:06 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/10 14:56:50 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*mydst;
	char			*mysrc;

	if (n > 0 && dst != src)
	{
		mydst = (char *)dst;
		mysrc = (char *)src;
		i = 0;
		while (i < n)
		{
			mydst[i] = mysrc[i];
			i++;
		}
	}
	return (dst);
}
