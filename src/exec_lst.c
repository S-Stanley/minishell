/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:11:14 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/19 22:52:06 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_next_stop(char **output, int i)
{
	int		count;

	count = 0;
	while (i < ft_len_matrice(output) && ft_strcmp(output[i], "|") != 0)
	{
		count++;
		i++;
	}
	return (count + 1);
}

t_token	*free_build_list(char **output, t_token *lst)
{
	free_that_matrice(output);
	free_token_list(lst);
	return (NULL);
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

int	find_stdin(char *cmd_line, char *next_cmd_line)
{
	if (ft_strcmp(cmd_line, "<") == 0)
		return (get_fd(next_cmd_line, 0, 0));
	if (ft_strcmp(cmd_line, "<<") == 0)
	{
		return (read_from_stdin(next_cmd_line));
	}
	return (0);
}

int	find_stdout(char *cmd_line, char *next_cmd_line)
{
	if (ft_strcmp(cmd_line, ">") == 0)
		return (get_fd(next_cmd_line, 0, 1));
	if (ft_strcmp(cmd_line, ">>") == 0)
		return (get_fd(next_cmd_line, 1, 1));
	return (1);
}

t_token	*build_lst(char	**output, int *exit_status)
{
	t_token	*lst;
	int		i;
	int		x;
	char	**cmd;
	int		fd_in;
	int		fd_out;

	i = -1;
	lst = NULL;
	fd_in = 0;
	fd_out = 1;
	while (++i < ft_len_matrice(output))
	{
		x = 0;
		cmd = malloc(sizeof(char *) * count_next_stop(output, i));
		if (!cmd)
			return (free_build_list(output, lst));
		while (output[i] && ft_strcmp(output[i], "|") != 0)
		{
			if (fd_in == 0)
				fd_in = find_stdin(output[i], output[i + 1]);
			if (fd_out == 1)
				fd_out = find_stdout(output[i], output[i + 1]);
			if (ft_strcmp(output[i], "<") == 0 || ft_strcmp(output[i], "<<") == 0)
			{
				i++;
				while (output[i] && ft_strcmp(output[i], "|") != 0)
					i++;
				break ;
			}
			if (ft_strcmp(output[i], ">") == 0 || ft_strcmp(output[i], ">>") == 0)
			{
				i++;
				while (output[i] && ft_strcmp(output[i], "|") != 0)
					i++;
				break ;
			}
			cmd[x] = get_cmd_arr(cmd, x, output[i], exit_status);
			if (!cmd[x])
				return (free_build_list(output, lst));
			i++;
			x++;
		}
		cmd[x] = NULL;
		lst = add_token(lst, fd_in, fd_out, cmd);
		fd_in = 0;
	}
	return (lst);
}

void	read_lst(t_token *lst)
{
	while (lst)
	{
		printf("%s\n", lst->exec_name);
		lst = lst->next;
	}
}

void	parse_and_exec(char	**output, char **env, int *exit_status)
{
	t_token	*lst;

	(void)env;
	lst = NULL;
	lst = build_lst(output, exit_status);
	if (!lst)
		return ;
	exec_cmd(lst, env, exit_status);
	free_that_matrice(output);
	free_token_list(lst);
}
