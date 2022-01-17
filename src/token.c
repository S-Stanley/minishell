/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:04 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/17 20:17:35 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *exec_name)
{
	(void)exec_name;
	return (0);
}

void	free_token_list(t_token *lst)
{
	t_token	*tmp;	

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

t_token	*create_token(int in_fd, int out_fd, char **cmd)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->cmd = cmd;
	new->exec_name = cmd[0];
	new->in_fd = in_fd;
	new->out_fd = out_fd;
	new->next = NULL;
	return (new);
}

t_token	*add_token(t_token *lst, int in_fd, int out_fd, char **cmd)
{
	t_token	*tmp;
	t_token	*new;

	new = create_token(in_fd, out_fd, cmd);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}
