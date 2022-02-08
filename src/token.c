/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:15:04 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/08 19:47:02 by sserbin          ###   ########.fr       */
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

void	free_token_list(t_token *lst)
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
		free(lst->cmd);
		free(lst);
		lst = tmp;
	}
}

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (true);
	if (ft_strcmp(str, "cd") == 0)
		return (true);
	if (ft_strcmp(str, "pwd") == 0)
		return (true);
	if (ft_strcmp(str, "export") == 0)
		return (true);
	if (ft_strcmp(str, "unset") == 0)
		return (true);
	if (ft_strcmp(str, "env") == 0)
		return (true);
	if (ft_strcmp(str, "exit") == 0)
		return (true);
	return (false);
}

t_token	*create_lst(char **cmd, char **redirections, char **env)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->infile = redirections[0];
	new->outfile = redirections[1];
	new->append = redirections[2];
	new->is_builtin = is_builtin(cmd[0]);
	new->cmd = cmd;
	new->exec_name = get_full_path(cmd[0], env);
	new->next = NULL;
	free(redirections);
	return (new);
}

t_token	*error_arg_for_token(char **matrice, t_token *lst)
{
	if (matrice)
		free_that_matrice(matrice);
	return (lst);
}

t_token	*add_lst(t_token *lst, char **cmd, char **redirections, char **env)
{
	t_token	*new;
	t_token	*tmp;

	if (!cmd)
		return (error_arg_for_token(redirections, lst));
	if (!redirections)
		return (error_arg_for_token(cmd, lst));
	new = create_lst(cmd, redirections, env);
	if (!new)
	{
		free(lst);
		return (lst);
	}
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}
