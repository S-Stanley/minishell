/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coop <coop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:13:51 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/27 09:48:17 by coop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	char	*applied;
	int		l;

	applied = NULL;
	if (s && f)
	{
		l = ft_strlen(s);
		applied = malloc(sizeof(char) * (l + 1));
		if (!applied)
			return (NULL);
		applied[l--] = '\0';
		while (l >= 0)
		{
			applied[l] = f(l, s[l]);
			l--;
		}
	}
	return (applied);
}
