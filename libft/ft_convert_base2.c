/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:34:51 by rokupin           #+#    #+#             */
/*   Updated: 2021/11/08 10:42:25 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	get_length(long dec, int base_val)
{
	int	l;

	l = 1;
	if (dec < 0)
	{
		l++;
		dec *= -1;
	}
	while (dec >= base_val)
	{
		dec /= base_val;
		l++;
	}
	return (l);
}

char	*dec_to_any(long dec, char *base, int base_val)
{
	char	*converted;
	int		length;
	int		i;

	length = get_length(dec, base_val) + 1;
	converted = (char *)malloc(sizeof(char) * length);
	i = 0;
	converted[--length] = '\0';
	if (dec < 0)
	{
		converted[0] = '-';
		dec *= -1;
		i++;
	}
	if (dec == 0)
		converted[0] = base[0];
	else
	{
		while (length > i)
		{
			converted[--length] = base[dec % base_val];
			dec /= base_val;
		}
	}
	return (converted);
}
