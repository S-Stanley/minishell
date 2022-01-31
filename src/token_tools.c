/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:14:20 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 02:14:41 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		printf("in %s out %s %d", lst->infile, lst->outfile, lst->is_builtin);
		printf("\n");
		lst = lst->next;
	}
}

t_token	*build_lst(char **line, char **env)
{
	unsigned int	i;
	t_token			*lst;

	lst = NULL;
	i = 0;
	while (line[i])
	{
		create_all_files(&line[i]);
		lst = add_lst(lst, full_cmd(&line[i]), get_redirection(&line[i]), env);
		if (!lst)
			return (NULL);
		while (line[i] && ft_strcmp(line[i], "|") != 0)
			i++;
		while (ft_strcmp(line[i], "|") == 0)
			i++;
	}
	return (lst);
}
