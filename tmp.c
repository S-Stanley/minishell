/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 01:33:36 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/17 02:46:53 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		fd2[2];
	int		status;
	char	*cmd[] = {"/bin/ls", "-l", 0};
	char	*cmd2[] = {"/usr/bin/grep", "dr", 0};
	char	*cmd3[] = {"/usr/bin/wc", "-l", 0};
	int		status2;

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(cmd[0], cmd, env);
	}
	else
	{
		wait(&status);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		pipe(fd2);
		if (fork() == 0)
		{
			close(fd2[0]);
			dup2(fd2[1], STDOUT_FILENO);
			close(fd2[1]);
			execve(cmd2[0], cmd2, env);
		}
		else
		{
			wait(&status2);
			close(fd2[1]);
			dup2(fd2[0], STDIN_FILENO);
			close(fd2[0]);
			execve(cmd3[0], cmd3, env);
		}
	}
	return (0);
}
