/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:53:43 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/16 09:52:45 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*dptr;
	char	*sptr;
	size_t	n;

	if (!dst || !src)
		return (0);
	n = dstsize;
	sptr = (char *)src;
	dptr = dst;
	if (n > 0)
		while (--n && *sptr)
			*dptr++ = *sptr++;
	if (dstsize)
		*dptr = '\0';
	while (*sptr)
		sptr++;
	return (sptr - src);
}
