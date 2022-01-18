/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:11:14 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/18 20:34:19 by sserbin          ###   ########.fr       */
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

int	get_fd(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (0);
	}
	return (fd);
}

int	find_stdin(char *cmd_line, char *next_cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '<')
			return (get_fd(next_cmd_line));
		i++;
	}
	return (0);
}

t_token	*build_lst(char	**output, int *exit_status)
{
	t_token	*lst;
	int		i;
	int		x;
	char	**cmd;
	int		fd_in;

	i = -1;
	lst = NULL;
	fd_in = 0;
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
			if (ft_strcmp(output[i], "<") == 0)
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
		lst = add_token(lst, fd_in, 1, cmd);
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
	exec_cmd(lst, env);
	free_that_matrice(output);
	free_token_list(lst);
}
