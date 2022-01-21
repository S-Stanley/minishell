/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/21 22:09:48 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(int fd_out, int *fd, t_token *lst, char **env)
{
	// close(fd[0]);
	if (lst->out_fd != 1)
	{
		dup2(lst->out_fd, STDOUT_FILENO);
		close(fd_out);
	}
	else if (lst->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	else
		close(fd[1]);
	close(fd[0]);
	execve(lst->exec_name, lst->cmd, env);
}

int	parent_process(int *fd, int fd_in, int fd_out, t_token *lst)
{
	close(fd[1]);
	if (fd_in != 0)
		close(fd_in);
	if (lst->in_fd)
	{
		fd_in = lst->in_fd;
		close(fd[0]);
	}
	else
		fd_in = fd[0];
	if (fd_out != 1)
		close(fd_out);
	if (!lst->next)
		close(fd[0]);
	return (fd_in);
}

void	set_status(int status, int *exit_status)
{
	if (status == 512)
		exit_status[0] = 2;
	if (status == 256)
		exit_status[0] = 1;
}

void	exec_cmd(t_token *lst, char **env, int *exit_status)
{
	int	status;
	int	fd[2];
	int	fd_in;
	int	fd_out;

	(void)exit_status;
	status = 0;
	fd_in = lst->in_fd;
	while (lst)
	{
		fd_out = lst->out_fd;
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			child_process(fd_out, fd, lst, env);
		}
		else
		{
			// if (ft_strcmp(lst->exec_name, "/bin/cat") != 0)
			// 	wait(&status);
			// set_status(status, exit_status);
			fd_in = parent_process(fd, fd_in, fd_out, lst);
		}
		lst = lst->next;
	}
	wait(&status);
	close(fd[0]);
	close(fd[1]);
}
