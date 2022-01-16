/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 11:23:00 by rokupin           #+#    #+#             */
/*   Updated: 2019/12/22 10:30:20 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp_ptr;

	if (lst)
	{
		ptr = *lst;
		while (ptr)
		{
			temp_ptr = NULL;
			if (ptr->next)
				temp_ptr = ptr->next;
			ft_lstdelone(ptr, del);
			ptr = temp_ptr;
		}
		*lst = NULL;
	}
}
