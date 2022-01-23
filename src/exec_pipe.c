/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/24 00:02:47 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	g_exit_status;

// void	child_process(int fd_out, int *fd, t_token *lst, char ***env)
// {
// 	if (lst->out_fd != 1)
// 	{
// 		// dup2(lst->out_fd, STDOUT_FILENO);
// 		// close(fd_out);
// 	}
// 	else if (lst->next != NULL)
// 		dup2(fd[1], STDOUT_FILENO);
// 	// else
// 		// close(fd[1]);
// 	// close(fd[0]);
// 	if (lst->is_builtin)
// 		exec_buildint(lst, env);
// 	else
// 		execve(lst->exec_name, lst->cmd, *env);
// }

// int	parent_process(int *fd, int fd_in, int fd_out, t_token *lst)
// {
// 	// close(fd[1]);
// 	// if (fd_in != 0)
// 		// close(fd_in);
// 	// if (lst->in_fd)
// 	// {
// 		// fd_in = lst->in_fd;
// 		// close(fd[0]);
// 	// }
// 	// else
// 		// fd_in = fd[0];
// 	// if (fd_out != 1)
// 		// close(fd_out);
// 	// if (!lst->next)
// 		// close(fd[0]);
// 	return (fd_in);
// }

void	set_status(int status)
{
	if (status == 512)
		g_exit_status = 2;
	if (status == 256)
		g_exit_status = 1;
}

void	exec_buildint(t_token *lst, char ***env)
{
	if (ft_strcmp(lst->cmd[0], "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(lst->cmd[0], "env") == 0)
		read_env(*env);
	if (ft_strcmp(lst->cmd[0], "export") == 0)
		*env = add_item_env(lst->cmd, *env);
	exit(0);
}

void	exec_cmd(t_token *lst, char ***env)
{
	int		fd[2];
	t_pid	*pid;
	pid_t	new_pid;
	int		infile;
	int		outfile;

	pid = NULL;
	while (lst)
	{
		pipe(fd);
		new_pid = fork();
		if (new_pid == 0)
		{
			pid = add_pid(pid, new_pid);
			close(fd[0]);
			if (lst->infile)
			{
				infile = open(lst->infile, O_RDONLY);
				dup2(infile, STDIN_FILENO);
				close(infile);
			}
			else
			{
				dup2(infile, STDIN_FILENO);
			}
			if (lst->next)
				dup2(fd[1], STDOUT_FILENO);
			if (lst->outfile)
			{
				outfile = open(lst->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
				dup2(outfile, STDOUT_FILENO);
			}
			execve(lst->exec_name, lst->cmd, *env);
		}
		else
		{
			close(fd[1]);
			if (lst->next)
				dup2(fd[0], STDIN_FILENO);
			pid = add_pid(pid, new_pid);
		}
		close(fd[0]);
		close(fd[1]);
		lst = lst->next;
	}
	dup2(STDOUT_FILENO, STDIN_FILENO);
	wait_all_pid(pid);
	free_pid(pid);
}