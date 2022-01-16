/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:45:31 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/15 16:30:42 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned int	i;
	unsigned char	cc;

	if (n)
	{
		cc = c;
		i = 0;
		str = (unsigned char *)s;
		while ((i < n) && (*str != cc))
		{
			str++;
			i++;
		}
		if (i < n)
			return ((void *)(str));
	}
	return (NULL);
}
