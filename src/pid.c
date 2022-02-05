/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:56:26 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 02:18:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pid	*create_pid(pid_t new_pid)
{
	t_pid	*new;

	new = malloc(sizeof(t_pid));
	new->pid = new_pid;
	new->next = NULL;
	return (new);
}

t_pid	*add_pid(t_pid *pid, pid_t new_pid)
{
	t_pid	*new;
	t_pid	*tmp;

	new = create_pid(new_pid);
	if (!new)
		return (pid);
	if (!pid)
		return (new);
	tmp = pid;
	while (pid->next)
		pid = pid->next;
	pid->next = new;
	return (tmp);
}

void	wait_all_pid(t_pid *pid)
{
	while (pid)
	{
		waitpid(pid->pid, &pid->status, 2);
		set_status(pid->status);
		pid = pid->next;
	}
}

void	free_pid(t_pid *pid)
{
	t_pid	*tmp;

	while (pid)
	{
		tmp = pid->next;
		free(pid);
		pid = tmp;
	}
}

void	set_status(int status)
{
	if (status == 512)
		g_exit_status = 2;
	else if (status == 256)
		g_exit_status = 1;
	else if (status == 127)
		g_exit_status = 127;
	else if (status == 32512)
		g_exit_status = 127;
	else if (status == 0)
		g_exit_status = 0;
}
