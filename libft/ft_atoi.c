/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:11:27 by rokupin           #+#    #+#             */
/*   Updated: 2021/11/08 10:32:44 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_num(const char *num, int negative)
{
	long	atoi;

	atoi = 0;
	while (*num >= '0' && *num <= '9')
	{
		atoi *= 10;
		atoi += *num - '0';
		num++;
		if (negative == -1 && atoi > 2147483648)
			return (0);
		else if (negative == 1 && atoi > 2147483647)
			return (-1);
	}
	return ((int)atoi * negative);
}

int	ft_atoi(const char *str)
{
	int		negative;
	char	*ptr;

	ptr = (char *)str;
	negative = 0;
	while ((*ptr >= 9 && *ptr <= 13) || *ptr == ' ')
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			negative++;
		ptr++;
	}
	if (negative > 0)
		negative = -1;
	else
		negative = 1;
	return (handle_num(ptr, negative));
}
