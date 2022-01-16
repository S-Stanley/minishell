/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 01:42:29 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 00:55:46 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list	*head;

	if (new && alst)
	{
		if (!(*alst))
			*alst = new;
		else
		{
			head = *alst;
			*alst = new;
			(*alst)->next = head;
		}
	}
}
