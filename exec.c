/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:24:51 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 21:27:44 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "include/libft.h"
#include "include/minishell.h"

t_token	*create_lst(char **cmd, int *redirections)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->in_fd = redirections[0];
	new->out_fd = redirections[1];
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

t_token	*add_lst(t_token *lst, char **cmd, int *redirections)
{
	t_token	*new;
	t_token	*tmp;

	if (!cmd || !redirections)
		return (lst);
	new = create_lst(cmd, redirections);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}

char	**full_cmd(char **str)
{
	return ((char **)str);
}

int	get_fd(char *filename, int append, int std)
{
	int	fd;

	if (!filename)
		return (std);
	if (append)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd = open(filename, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
	{
		close(fd);
		return (std);
	}
	return (fd);
}

int	read_from_stdin(char *next_cmd_line)
{
	int		reading;
	char	*buffer;
	int		fd_to_write;
	char	*to_stop;

	to_stop = ft_strjoin(next_cmd_line, "\n");
	fd_to_write = open("/tmp/.listen-stdin", O_RDWR | O_CREAT, 0777);
	while (1)
	{
		buffer = malloc(sizeof(char) * 100);
		reading = read(0, buffer, 99);
		buffer[reading] = 0;
		if (ft_strcmp(buffer, to_stop) == 0)
		{
			free(to_stop);
			write(fd_to_write, buffer, ft_strlen(buffer));
			close(fd_to_write);
			free(buffer);
			break ;
		}
		free(buffer);
	}
	return (get_fd("/tmp/.listen-stdin", 0, 0));
}

int	*get_redirection(char **str)
{
	unsigned int	i;
	int				*fd;

	i = 0;
	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 1;
	while (str[i] && ft_strcmp(str[i], "|") != 0)
	{
		if (ft_strcmp(str[i], "<") == 0)
			fd[0] = get_fd(str[i + 1], 0, 0);
		if (ft_strcmp(str[i], "<<") == 0)
			fd[0] = read_from_stdin(str[i + 1]);
		if (ft_strcmp(str[i], ">") == 0)
			fd[1] = get_fd(str[i + 1], 0, 1);
		if (ft_strcmp(str[i], ">>") == 0)
			fd[1] = get_fd(str[i + 1], 1, 1);
		i++;
	}
	return (fd);
}

int	count_len_matrice(char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return (0);
	while (matrice[i])
		i++;
	return (i);
}

t_token	*build_lst(char **cmd_line)
{
	unsigned int	i;
	t_token			*lst;
	char			*ptr;

	lst = NULL;
	i = 0;
	while (cmd_line[i])
	{
		lst = add_lst(lst, full_cmd(&cmd_line[i]), get_redirection(&cmd_line[i]));
		if (!lst)
			return (NULL);
		while (cmd_line[i] && ft_strcmp((char *)cmd_line[i], "|") != 0)
			i++;
		while (ft_strcmp((char *)cmd_line[i], "|") == 0)
			i++;
	}
	return (lst);
}

// bool	exec_cmd(t_token *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s\n", lst->full_cmd[0]);
// 		lst = lst->next;
// 	}
// 	return (true);
// }

void	free_lst(t_token *lst)
{
}

bool	exec(char **cmd_line, char **env, int *exit_status)
{
	t_token	*lst;

	lst = NULL;
	lst = build_lst((char **)cmd_line);
	if (!lst)
		return (false);
	exec_cmd(lst, env, exit_status);
	// free(cmd_line);
	// free_lst(lst);
	return (true);
}

int main(int ac, char **av, char **env)
{
	char	*cmd[] = {"ls", "-l", "|", "wc", 0};
	int		*exit_status;

	exit_status = malloc(sizeof(int));
	exit_status[0] = 0;
	exec(cmd, env, exit_status);
	return (0);
}
