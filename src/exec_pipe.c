/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 22:57:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_token *lst, char **env, int *exit_status)
{
	int	status;
	int	fd[2];
	int	fd_in;
	int	fd_out;

	fd_in = lst->in_fd;
	while (lst)
	{
		fd_out = lst->out_fd;
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			if (lst->out_fd != 1)
			{
				dup2(lst->out_fd, STDOUT_FILENO);
				close(fd_out);
			}
			else if (lst->next != NULL)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			execve(lst->exec_name, lst->cmd, env);
		}
		else
		{
			wait(&status);
			if (status == 512)
				exit_status[0] = 2;
			if (status == 256)
				exit_status[0] = 1;
			close(fd[1]);
			if (fd_in != 0)
				close(fd_in);
			if (lst->in_fd)
				fd_in = lst->in_fd;
			else
				fd_in = fd[0];
			if (fd_out != 1)
				close(fd_out);
		}
		lst = lst->next;
	}
}
