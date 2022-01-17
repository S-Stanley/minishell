/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 00:40:37 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/17 02:36:17 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

typedef struct s_token
{
	char			**cmd;
	char			*exec_name;
	int				is_builtin;
	int				in_fd;
	int				out_fd;
	struct s_token	*next;
}	t_token;

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
	if (fork() == 0)
	{
		if (lst->in_fd != -1)
			dup2(lst->in_fd, STDIN_FILENO);
		if (lst->out_fd != -1)
			dup2(lst->out_fd, STDOUT_FILENO);
		execve(lst->exec_name, lst->cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*cmd[] = {"/bin/ls", "-l", 0};
	char	*cmd2[] = {"/usr/bin/grep", "dr", 0};
	char	*cmd3[] = {"/usr/bin/wc", "-l", 0};
	t_token	*lst;
	int		fd[2];
	int		fd2[2];

	lst = NULL;
	pipe(fd);
	pipe(fd2);
	lst = add_token(lst, -1, fd[1], cmd);
	lst = add_token(lst, fd[0], fd2[1], cmd2);
	lst = add_token(lst, fd2[0], -1, cmd3);
	while (lst)
	{
		exec_cmd(lst, env);
		lst = lst->next;
	}
	return (0);
}
