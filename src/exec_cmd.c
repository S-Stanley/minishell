/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/17 20:16:09 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_token *lst, char **env)
{
	int	status;
	int	fd[2];
	int	fd_in;

	fd_in = 0;
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
			fd_in = fd[0];
		}
		lst = lst->next;
	}
}
