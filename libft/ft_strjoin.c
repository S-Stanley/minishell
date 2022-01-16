/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:13:08 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 01:06:11 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	long	l1;
	long	l2;
	char	*res;

	l1 = 0;
	l2 = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[l1])
		l1++;
	while (s2[l2])
		l2++;
	res = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!res)
		return (NULL);
	res[l1 + l2] = '\0';
	while (--l2 >= 0)
		res[l1 + l2] = s2[l2];
	while (--l1 >= 0)
		res[l1] = s1[l1];
	return (res);
}
