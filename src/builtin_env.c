/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:37:29 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/22 19:05:13 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_env(char **env)
{
	char	**to_return;
	int		i;

	if (!env)
		return (NULL);
	to_return = malloc(sizeof(char *) * (count_len_matrice(env) + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	while (env[i])
	{
		to_return[i] = env[i];
		i++;
	}
	to_return[i] = 0;
	return (to_return);
}

char	**add_item_env(char **cmd, char **env)
{
	int		i;
	char	**to_return;

	if (!env || !cmd)
		return (env);
	to_return = malloc(sizeof(char *) * (count_len_matrice(env) + 2));
	i = 0;
	while (env[i])
	{
		to_return[i] = env[i];
		i++;
	}
	to_return[i] = cmd[1];
	to_return[++i] = 0;
	return (to_return);
}
