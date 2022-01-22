/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:24:51 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/22 19:07:40 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_splitter(void)
{
	char	**splitter;

	splitter = malloc(sizeof(char **) * 6);
	splitter[0] = "|";
	splitter[1] = "<";
	splitter[2] = "<<";
	splitter[3] = ">";
	splitter[4] = ">>";
	splitter[5] = 0;
	return (splitter);
}

char	**full_cmd(char **str)
{
	char	**to_return;
	char	**to_split;

	to_split = get_splitter();
	to_return = ft_matrice_split(str, to_split);
	return (to_return);
}

void	read_lst(t_token *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			printf("%s ", lst->cmd[i]);
			i++;
		}
		printf("\n");
		lst = lst->next;
	}
}

t_token	*build_lst(char **line)
{
	unsigned int	i;
	t_token			*lst;

	lst = NULL;
	i = 0;
	while (line[i])
	{
		lst = add_lst(lst, full_cmd(&line[i]), get_redirection(&line[i]));
		if (!lst)
			return (NULL);
		while (line[i] && ft_strcmp((char *)line[i], "|") != 0)
			i++;
		while (ft_strcmp((char *)line[i], "|") == 0)
			i++;
	}
	return (lst);
}

bool	exec(char **cmd_line, char ***env, int *exit_status)
{
	t_token	*lst;

	lst = NULL;
	lst = build_lst((char **)cmd_line);
	if (!lst)
		return (false);
	exec_cmd(lst, env, exit_status);
	free_token_list(lst);
	return (true);
}
