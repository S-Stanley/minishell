/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:59:13 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/06 18:59:28 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**export_something(char ***env, char **cmd, t_token *lst)
{
	*env = update_env(lst->cmd, *env);
	if (lst->next)
		exec_cmd(lst->next, env, cmd);
	return (*env);
}
