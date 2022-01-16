/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:32:08 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/16 21:35:04 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>
#include <fcntl.h>

// struct s_token
// {
// 	char	**cmd;
// 	char	*exec_name;
// 	int		is_builtin;
// 	int		in_fd;
// 	int		out_fd;
// 	t_token	*next;
// };

// ls -l | grep src | wc -c
// {"ls", "-l", 0}

int	is_builtin(char *exec_name)
{
	return (0);
}

void	free_token_list(t_token *lst)
{
	t_token	*tmp;	

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

t_token	*create_token(int in_fd, int out_fd, char **cmd)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->cmd = cmd;
	new->exec_name = cmd[0];
	new->in_fd = in_fd;
	new->out_fd = out_fd;
	new->is_builtin = is_builtin(cmd[0]);
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

void	child_process(int *fd, t_token *lst, char **env)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execve(lst->cmd[0], lst->cmd, env);
}

void	parent_process(int *fd, t_token *lst, char **env)
{
	int	status;

	wait(&status);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execve(lst->cmd[0], lst->cmd, env);
}

void	exec_cmd(t_token *lst, t_token *lst2, char **env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pid = fork();
	pipe(fd);
	if (pid == -1)
	{
		printf("Error pipe\n");
		exit(1);
	}
	if (pid == 0)
		child_process(fd, lst, env);
	else
		parent_process(fd, lst2, env);
}

int	main(int ac, char **av, char **env)
{	
	t_token	*lst;
	t_token	*tmp;
	char	*cmd1[] = {"/bin/ls", "-l", 0};
	char	*cmd2[] = {"/usr/bin/grep", "a", 0};
	char	*cmd3[] = {"/usr/bin/wc", 0};

	(void)ac;
	(void)av;
	lst = NULL;
	lst = add_token(lst, -1, 1, cmd1);
	lst = add_token(lst, 1, 1, cmd2);
	lst = add_token(lst, 1, 1, cmd3);
	tmp = lst;
	exec_cmd(lst, lst->next->next, env);
	// while (lst)
	// {
	// 	exec_cmd(lst, lst->next, env);
	// 	lst = lst->next->next;
	// }
	free_token_list(tmp);
	return (0);
}

/*
	exec_cmd function

	Get the correct executable:
		1. Check if it's the executable is a built in
		2. Search for command in path if env not null
		3. Check search for absolute path if there is a /
		4. If not found print command not found

	Executing the command:
		1. Get input
		2. Doing the execve
		3. Send the output to the right output fd
*/
