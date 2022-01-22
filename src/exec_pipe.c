/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/22 18:00:25 by sserbin          ###   ########.fr       */
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

typedef struct s_pid {
	pid_t			pid;
	int				status;
	struct s_pid	*next;
}	t_pid;

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

void	wait_all_pid(t_pid *pid, int *exit_status)
{
	while (pid)
	{
		waitpid(pid->pid, &pid->status, 2);
		set_status(pid->status, exit_status);
		pid = pid->next;
	}
}

void	exec_buildint(t_token *lst)
{
	if (ft_strcmp(lst->cmd[0], "cd") == 0)
		builtin_cd(lst->cmd[1]);
}

void	exec_cmd(t_token *lst, char **env, int *exit_status)
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	t_pid	*pid;
	pid_t	new_pid;

	pid = NULL;
	fd_in = lst->in_fd;
	while (lst)
	{
		if (lst->is_builtin)
			exec_buildint(lst);
		else
		{
			pipe(fd);
			fd_out = lst->out_fd;
			new_pid = fork();
			if (new_pid == 0)
			{
				pid = add_pid(pid, new_pid);
				dup2(fd_in, STDIN_FILENO);
				child_process(fd_out, fd, lst, env);
			}
			else
			{
				pid = add_pid(pid, new_pid);
				fd_in = parent_process(fd, fd_in, fd_out, lst);
			}
		}
		lst = lst->next;
	}
	wait_all_pid(pid, exit_status);
}
