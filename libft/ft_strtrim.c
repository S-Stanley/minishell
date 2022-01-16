/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coop <coop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:01:40 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 01:08:13 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	present(char c, const char *set)
{
	while (*set && *set != c)
		set++;
	if (*set == c)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char		*s2;
	char			*ret;
	int				i;

	if (s1 && set && *s1)
	{
		ret = NULL;
		i = -1;
		s2 = s1 + ft_strlen(s1);
		while (*s1 && present(*s1, set))
			s1++;
		while (s2 >= s1 && present(*s2, set))
			s2--;
		if (s2 != s1)
		{
			ret = malloc(sizeof(char) * (2 + s2 - s1));
			if (!ret)
				return (NULL);
			while (++i <= (s2 - s1))
				ret[i] = s1[i];
			ret[i] = '\0';
		}
		return (ret);
	}
	return (ft_strdup(""));
}
