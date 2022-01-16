/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 01:43:47 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 00:57:49 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*new_ptr;
	t_list	*new;

	new = ft_lstnew(f(lst->content));
	if (lst && f && del)
	{
		new_ptr = new;
		ptr = lst->next;
		while (ptr)
		{
			new_ptr->next = ft_lstnew(f(ptr->content));
			new_ptr = new_ptr->next;
			if (!new_ptr)
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ptr = ptr->next;
		}
	}
	return (new);
}
