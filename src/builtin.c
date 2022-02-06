/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:18:43 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/06 19:48:06 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_fds(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(2);
}

void	free_the_rest(char **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
}

void	exec_buildint(t_token *lst, char ***env, char **cmd)
{
	if (ft_strcmp(lst->cmd[0], "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(lst->cmd[0], "env") == 0)
		read_env(*env);
	if (ft_strcmp(lst->cmd[0], "export") == 0 && !lst->cmd[1])
		read_export(*env);
	if (ft_strcmp(lst->cmd[0], "export") == 0 && lst->cmd[1])
		*env = update_env(lst->cmd, *env);
	if (ft_strcmp(lst->cmd[0], "echo") == 0)
		builtin_echo(lst->cmd);
	free_the_rest(&cmd[1]);
	free(lst->exec_name);
	free_token_list(lst);
	free_that_matrice(*env);
	free(cmd);
	close_fds();
	exit(0);
}
