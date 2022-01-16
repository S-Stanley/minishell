/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:05:51 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/11 17:25:59 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hp;
	char	*np;
	size_t	l;

	if (!*needle)
		return ((char *)haystack);
	while (len && (*haystack || (!*haystack && !*needle)))
	{
		hp = (char *)haystack;
		np = (char *)needle;
		l = len;
		while (*hp && *np && *np == *hp && l)
		{
			np++;
			hp++;
			l--;
		}
		if (!*np)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
