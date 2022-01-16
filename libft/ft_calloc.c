/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:28:37 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/12 12:11:22 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			fsize;
	void			*allocated;
	unsigned char	*ptr;

	fsize = count * size;
	allocated = malloc(fsize);
	if (!allocated)
		return (NULL);
	ptr = allocated;
	while (fsize)
	{
		*(ptr++) = 0;
		fsize--;
	}
	return (allocated);
}
