/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 03:17:28 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/10 10:27:54 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*mydst;
	unsigned char	*mysrc;

	mydst = (unsigned char *)dst;
	mysrc = (unsigned char *)src;
	if (len > 0 && dst != src)
	{
		if (src < dst)
		{
			mydst += len;
			mysrc += len;
			while (len-- > 0)
				*(--mydst) = *(--mysrc);
		}
		else
			while (len-- > 0)
				*(mydst++) = *(mysrc++);
	}
	return (dst);
}
