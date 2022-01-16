/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coop <coop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:15:06 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 00:54:58 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_range(int n, int negative)
{
	int		range;

	range = 1 + negative;
	while (n >= 10)
	{
		n /= 10;
		range++;
	}
	return (range);
}

static char	*itoa(int n)
{
	int		fix;
	int		negative;
	int		range;
	char	*a;

	negative = 0;
	if (n < 0)
		negative = 1;
	if (negative)
		n *= -1;
	fix = n;
	range = get_range(n, negative);
	a = malloc(sizeof(char) * (range + 1));
	if (!a)
		return (NULL);
	a[range--] = '\0';
	if (negative && range--)
		a[0] = '-';
	while (range >= 0)
	{
		a[range + negative] = (fix % 10) + '0';
		fix /= 10;
		range--;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (itoa(n));
}
