/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:18:43 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 02:19:03 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_buildint(t_token *lst, char ***env)
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
	free_that_matrice(lst->cmd);
	free(lst->exec_name);
	exit(0);
}
