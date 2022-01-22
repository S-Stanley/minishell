/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:04:19 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 23:04:31 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
