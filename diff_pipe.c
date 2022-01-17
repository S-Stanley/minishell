/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 02:36:33 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/17 02:50:55 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void	exec_cmd(char **cmd, char **env, int in, int out)
{
	if (fork() == 0)
	{
		if (in != -1)
			dup2(in, STDIN_FILENO);
		if (out != -1)
			dup2(out, STDOUT_FILENO);
		execve(cmd[0], cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*cmd[] = {"/bin/ls", "-l", 0};
	char	*cmd2[] = {"/usr/bin/grep", "dr", 0};
	char	*cmd3[] = {"/usr/bin/wc", "-l", 0};
	int		fd[2];
	int		fd2[2];

	pipe(fd);
	pipe(fd2);
	exec_cmd(cmd, env, -1, fd[1]);
	exec_cmd(cmd2, env, fd[0], -1);
	// exec_cmd(cmd2, env, fd[0], fd2[1]);
	// exec_cmd(cmd3, env, fd2[0], -1);
	return (0);
}
