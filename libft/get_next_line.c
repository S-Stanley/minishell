/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:22:05 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 08:45:29 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 10
#define FD 2049

int	find_nl(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n')
	{
		if (!s[i])
			return (-1);
		i++;
	}
	if (s[i] == '\n')
		return (i + 1);
	return (i);
}

char	*extract_substr(char **s1, int len)
{
	char	*ret;
	char	*rest;

	ret = ft_strndup(*s1, len - 1);
	rest = ft_strndup(*s1 + len, 0x7fffffff);
	free(*s1);
	*s1 = rest;
	return (ret);
}

int	init_check_wrong_data(int fd, char **line, int *chrs_to_nl, int *chrs_red)
{
	char	*read_buff;
	int		ret;

	ret = 0;
	read_buff = NULL;
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		ret = 1;
	*chrs_red = read(fd, read_buff, 0);
	if (*chrs_red < 0)
		ret = 1;
	*chrs_red = 0;
	*chrs_to_nl = -1;
	return (ret);
}

int	set_line(int chrs_to_nl, int chrs_red, char **fd_s, char **line)
{
	if (chrs_to_nl < 0 && !chrs_red)
	{
		if (ft_strlen(*fd_s))
			*line = ft_strndup(*fd_s, 0x7fffffff);
		else
			*line = ft_strndup("", 1);
		free(*fd_s);
		*fd_s = NULL;
		return (0);
	}
	if (chrs_to_nl > 0)
		*line = extract_substr(fd_s, chrs_to_nl);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*fd_s[FD + 1];
	char		*read_buff;
	int			chrs_to_nl;
	int			chrs_red;

	if (init_check_wrong_data(fd, line, &chrs_to_nl, &chrs_red))
		return (-1);
	if (fd_s[fd])
		chrs_to_nl = find_nl(fd_s[fd]);
	else
		fd_s[fd] = ft_strndup("", 1);
	while (chrs_to_nl < 0)
	{
		read_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		chrs_red = read(fd, read_buff, BUFFER_SIZE);
		read_buff[chrs_red] = '\0';
		if (!chrs_red)
		{
			free(read_buff);
			break ;
		}
		fd_s[fd] = ft_strcat(read_buff, fd_s[fd]);
		chrs_to_nl = find_nl(fd_s[fd]);
	}
	return (set_line(chrs_to_nl, chrs_red, &(fd_s[fd]), line));
}
