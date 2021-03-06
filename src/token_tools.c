/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:14:20 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/08 21:39:57 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_that_matrice_light(char **matrice)
{
	unsigned int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		if (matrice[i])
			free(matrice[i]);
		i++;
	}
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

void	free_token_light(t_token *lst)
{
	t_token	*tmp;	

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		if (!lst->is_builtin)
			free(lst->exec_name);
		if (lst->infile)
			free(lst->infile);
		if (lst->outfile)
			free(lst->outfile);
		if (lst->append)
			free(lst->append);
		free_that_matrice(lst->cmd);
		free(lst);
		lst = tmp;
	}
}
