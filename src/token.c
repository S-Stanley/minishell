/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:04 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 16:32:42 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token_list(t_token *lst)
{
	t_token	*tmp;	

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->exec_name);
		free(lst->cmd);
		free(lst);
		lst = tmp;
	}
}

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (true);
	if (ft_strcmp(str, "cd") == 0)
		return (true);
	if (ft_strcmp(str, "pwd") == 0)
		return (true);
	if (ft_strcmp(str, "export") == 0)
		return (true);
	if (ft_strcmp(str, "unset") == 0)
		return (true);
	if (ft_strcmp(str, "env") == 0)
		return (true);
	if (ft_strcmp(str, "exit") == 0)
		return (true);
	return (false);
}

t_token	*create_lst(char **cmd, int *redirections)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->in_fd = redirections[0];
	new->out_fd = redirections[1];
	new->is_builtin = is_builtin(cmd[0]);
	new->cmd = cmd;
	new->exec_name = get_full_path(cmd[0]);
	if (!new->exec_name)
	{
		free(redirections);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	free(redirections);
	return (new);
}

t_token	*add_lst(t_token *lst, char **cmd, int *redirections)
{
	t_token	*new;
	t_token	*tmp;

	if (!cmd || !redirections)
		return (lst);
	new = create_lst(cmd, redirections);
	if (!new)
	{
		free(lst);
		return (NULL);
	}
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}
