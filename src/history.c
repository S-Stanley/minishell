/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:54:50 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 16:55:03 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_history	*create_new_history(char *to_add)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	if (!new)
		return (NULL);
	new->str = to_add;
	new->next = NULL;
	return (new);
}

t_history	*add_cmd_line(t_history *cmd, char *to_add)
{
	t_history	*new;
	t_history	*tmp;

	new = create_new_history(to_add);
	if (!new)
		return (cmd);
	if (!cmd)
		return (new);
	tmp = cmd;
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = new;
	return (tmp);
}

void	free_history(t_history *history)
{
	t_history	*tmp;

	while (history)
	{
		tmp = history->next;
		free(history->str);
		free(history);
		history = tmp;
	}
}
