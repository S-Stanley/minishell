/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:32:08 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/12 14:39:53 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		l;
	char	*dup;

	l = 0;
	while (s1[l])
		l++;
	dup = malloc(sizeof(char) * (l + 1));
	if (!dup)
		return (NULL);
	dup[l--] = '\0';
	while (l >= 0)
	{
		dup[l] = s1[l];
		l--;
	}
	return (dup);
}
