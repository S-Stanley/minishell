/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:35:27 by rokupin           #+#    #+#             */
/*   Updated: 2021/11/09 00:56:11 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	get_long_range(unsigned long long n)
{
	int	range;

	range = 1;
	while (n >= 10)
	{
		n /= 10;
		range++;
	}
	return (range);
}

char	*fill(unsigned long long val, int neg, int range)
{
	char	*ret;
	int		mod;

	if (!neg)
		mod = 1;
	else
		mod = 2;
	ret = malloc(sizeof(char) * (range + mod));
	ret[range + --mod] = '\0';
	range--;
	if (neg == 1)
		ret[0] = '-';
	else if (neg == 2)
		ret[0] = '.';
	while (range >= 0)
	{
		ret[range + mod] = (val % 10) + '0';
		val /= 10;
		range--;
	}
	return (ret);
}

char	*pr_fl_tostring(double d, int prec)
{
	char	*s;
	int		buf;
	int		i;

	i = 1;
	s = malloc(sizeof(char) * (prec + 2));
	s[prec + 1] = '\0';
	s[0] = '.';
	while (prec--)
	{
		d *= 10;
		buf = ((int)d) % 10;
		s[i++] = buf + '0';
		d -= buf;
	}
	return (s);
}

char	*ft_dtoa(double d, int prec)
{
	char				*i_p;
	int					negative;
	unsigned long long	i_part;
	double				f_part;

	negative = 0;
	if (d < 0)
		negative = 1;
	if (!negative)
	{
		i_part = (unsigned long long)d;
		f_part = d - i_part;
	}
	if (negative)
	{		
		i_part = (unsigned long long)(d * -1);
		f_part = (d * -1) - i_part;
	}
	i_p = fill(i_part, negative, get_long_range(i_part));
	return (ft_strcat(pr_fl_tostring(f_part, prec), i_p));
}
