/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:10:11 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 08:40:12 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcat(char *src, char *dst)
{
	char	*ret;
	int		i;
	int		j;

	if (!src)
		return (dst);
	if (!dst)
		return (src);
	i = 0;
	j = 0;
	while (src[i])
		i++;
	while (dst[j])
		j++;
	ret = malloc(sizeof(char) * (i + j + 1));
	ret[i + j] = '\0';
	while (--i >= 0)
		ret[i + j] = src[i];
	while (--j >= 0)
		ret[j] = dst[j];
	free(src);
	free(dst);
	return (ret);
}

char	*ft_strndup(char *s1, int len)
{
	char	*dup;
	int		l;

	l = 0;
	while (s1[l])
		l++;
	if (l > len)
		l = len;
	dup = malloc(sizeof(char) * (l + 1));
	if (!dup)
		return (NULL);
	dup[l] = '\0';
	l--;
	while (l >= 0)
	{
		dup[l] = s1[l];
		l--;
	}
	return (dup);
}
