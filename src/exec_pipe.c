/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/03 21:21:39 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_executable(t_token *lst, char ***env, char **cmd)
{
	if (access(lst->exec_name, X_OK) == 0)
		execve(lst->exec_name, lst->cmd, *env);
	free_token_light(lst);
	free_that_matrice(*env);
	free(cmd);
	exit(127);
}

bool	child_process(t_token *lst, int *fd, char ***env, char **cmd)
{
	int		infile;

	signal(SIGINT, exit_handler);
	signal(SIGQUIT, exit_handler);
	close(fd[0]);
	if (lst->infile)
	{
		infile = open(lst->infile, O_RDONLY);
		dup2(infile, STDIN_FILENO);
		close(infile);
		unlink("/tmp/.listen-stdin");
	}
	if (lst->next)
		dup2(fd[1], STDOUT_FILENO);
	if (lst->outfile)
		get_outfile(lst);
	close(fd[1]);
	if (lst->is_builtin)
		exec_buildint(lst, env, cmd);
	else
		run_executable(lst, env, cmd);
	return (false);
}

bool	parent_process(int *fd, t_token *lst)
{
	close(fd[1]);
	if (lst->next)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (true);
}

void	finish_exec(t_pid *pid)
{
	dup2(STDOUT_FILENO, STDIN_FILENO);
	wait_all_pid(pid);
	free_pid(pid);
}

void	exec_cmd(t_token *lst, char ***env, char **cmd)
{
	int		fd[2];
	t_pid	*pid;
	pid_t	new_pid;

	pid = NULL;
	while (lst)
	{
		pipe(fd);
		new_pid = fork();
		if (new_pid == 0)
			child_process(lst, fd, env, cmd);
		else
		{
			parent_process(fd, lst);
			pid = add_pid(pid, new_pid);
		}
		close(fd[0]);
		close(fd[1]);
		lst = lst->next;
	}
	finish_exec(pid);
}
