/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 00:10:44 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/14 14:10:48 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	char			stop;
	char			*mydst;
	char			*mysrc;

	if (n > 0 && src != dst)
	{
		mydst = (char *)dst;
		mysrc = (char *)src;
		i = 0;
		stop = c;
		while (i < n)
		{
			*mydst = mysrc[i];
			if (mysrc[i] == stop)
				return (++mydst);
			mydst++;
			i++;
		}
	}
	return (NULL);
}
