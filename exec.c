/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:24:51 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 20:57:39 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "include/libft.h"

typedef struct s_lst {
	int		fd_in;
	int		fd_out;
	char	**full_cmd;
	void	*next;
}	t_lst;

t_lst	*create_lst(char **cmd, int *redirections)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	// new->fd_in = redirections[0];
	// new->fd_out = redirections[1];
	new->full_cmd = cmd;
	new->next = NULL;
	return (new);
}

t_lst	*add_lst(t_lst *lst, char **cmd, int *redirections)
{
	t_lst	*new;
	t_lst	*tmp;

	// if (!cmd || !redirections)
	// 	return (lst);
	new = create_lst(cmd, redirections);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}

char	**full_cmd(const char **str)
{
	return ((char **)str);
}

int	*get_redirection(const char **str)
{
	(void)str;
	return (NULL);
}

int	count_len_matrice(const char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return (0);
	while (matrice[i])
		i++;
	return (i);
}

t_lst	*build_lst(const char **cmd_line)
{
	unsigned int	i;
	t_lst			*lst;
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

bool	exec_cmd(t_lst *lst)
{
	while (lst)
	{
		printf("%s\n", lst->full_cmd[0]);
		lst = lst->next;
	}
	return (true);
}

void	free_lst(t_lst *lst)
{
}

bool	exec(char **cmd_line)
{
	t_lst	*lst;

	lst = NULL;
	lst = build_lst((const char **)cmd_line);
	if (!lst)
		return (false);
	exec_cmd(lst);
	// free(cmd_line);
	// free_lst(lst);
	return (true);
}

int main(void)
{
	char	*cmd[] = {"ls", "-l", "|", "wc", 0};

	exec(cmd);
	return (0);
}
