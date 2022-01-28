/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:04:19 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/28 20:26:47 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_fd(char *filename)
{
	if (!filename)
		return (ft_strdup(""));
	return (ft_strdup(filename));
}

char	*read_from_stdin(char *next_cmd_line)
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
	return (get_fd("/tmp/.listen-stdin"));
}

bool	string_is_separator(char *str, char *separators)
{
	char			**sep;
	unsigned int	x;

	sep = ft_split(separators, ' ');
	x = 0;
	while (sep[x])
	{
		if (ft_strcmp(str, sep[x]) == 0)
		{
			free_that_matrice(sep);
			return (true);
		}
		x++;
	}
	free_that_matrice(sep);
	return (false);
}

char	**get_redirection(char **str)
{
	unsigned int	i;
	char			**files;

	i = 0;
	files = malloc(sizeof(char *) * 3);
	files[0] = NULL;
	files[1] = NULL;
	while (str[i])
	{
		if (ft_strcmp(str[i], "<") == 0)
			files[0] = get_fd(str[i + 1]);
		if (ft_strcmp(str[i], "<<") == 0)
			files[0] = read_from_stdin(str[i + 1]);
		if (ft_strcmp(str[i], ">") == 0)
			files[1] = get_fd(str[i + 1]);
		if (ft_strcmp(str[i], ">>") == 0)
			files[1] = get_fd(str[i + 1]);
		if (ft_strcmp(str[i], "|") == 0)
			break ;
		i++;
	}
	files[2] = 0;
	return (files);
}
