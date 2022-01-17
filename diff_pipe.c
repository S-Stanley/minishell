/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 02:36:33 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/17 19:31:10 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "include/minishell.h"

t_token	*create_token(int in_fd, int out_fd, char **cmd)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->cmd = cmd;
	new->exec_name = cmd[0];
	new->in_fd = in_fd;
	new->out_fd = out_fd;
	new->next = NULL;
	return (new);
}

t_token	*add_token(t_token *lst, int in_fd, int out_fd, char **cmd)
{
	t_token	*tmp;
	t_token	*new;

	new = create_token(in_fd, out_fd, cmd);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}

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

int	main(int ac, char **av, char **env)
{
	char	*ls[] = {"/bin/ls", "-l", 0};
	char	*grep[] = {"/usr/bin/grep", "a", 0};
	char	*wc[] = {"/usr/bin/wc", 0};
	// char	*wc2[] = {"/usr/bin/wc", "-c", 0};
	t_token	*lst;

	lst = NULL;
	lst = add_token(lst, -1, 1, ls);
	lst = add_token(lst, 1, 1, grep);
	lst = add_token(lst, 1, 1, wc);
	// lst = add_token(lst, 1, 1, wc2);
	exec_cmd(lst, env);
	return (0);
}
