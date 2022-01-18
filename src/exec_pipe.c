/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/18 20:33:59 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_token *lst, char **env)
{
	int	status;
	int	fd[2];
	int	fd_in;

	fd_in = lst->in_fd;
	while (lst)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			if (lst->next != NULL)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			execve(lst->exec_name, lst->cmd, env);
		}
		else
		{
			wait(&status);
			close(fd[1]);
			if (fd_in != 0)
				close(fd_in);
			if (lst->in_fd)
				fd_in = lst->in_fd;
			else
				fd_in = fd[0];
		}
		lst = lst->next;
	}
}
