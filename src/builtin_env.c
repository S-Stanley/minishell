/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:37:29 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 17:13:56 by sserbin          ###   ########.fr       */
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
		to_return[i] = ft_strdup(env[i]);
		i++;
	}
	to_return[i] = 0;
	return (to_return);
}

char	**add_item_env(char **cmd, char **env)
{
	int		i;
	char	**to_return;
	int		x;

	if (!env || !cmd)
		return (env);
	to_return = malloc(sizeof(char *)
			* (count_len_matrice(env) + count_len_matrice(&cmd[1]) + 1));
	if (!to_return)
		return (env);
	i = 0;
	while (env[i])
	{
		to_return[i] = ft_strdup(env[i]);
		i++;
	}
	x = 1;
	while (cmd[x])
	{
		to_return[i] = ft_strdup(cmd[x]);
		x++;
		i++;
	}
	to_return[i] = 0;
	free_that_matrice(env);
	return (to_return);
}

bool	find_string_in_matrice(char *to_find, char **matrice)
{
	unsigned int	i;
	char			**var;

	i = 0;
	if (!to_find || !matrice)
		return (false);
	while (matrice[i])
	{
		var = ft_split(to_find, '=');
		if (ft_strcmp(var[0], matrice[i]) == 0)
		{
			free_that_matrice(var);
			return (true);
		}
		free_that_matrice(var);
		i++;
	}
	return (false);
}

char	**remove_item_env(char **cmd, char **env)
{
	int		i;
	char	**to_return;
	int		x;

	if (!cmd || !env)
		return (env);
	to_return = malloc(sizeof(char *)
			* (count_len_matrice(env) - count_len_matrice(&cmd[1]) + 1));
	if (!to_return)
		return (env);
	i = 0;
	x = 0;
	while (env[i])
	{
		if (!find_string_in_matrice(env[i], &cmd[1]))
		{
			to_return[x] = ft_strdup(env[i]);
			x++;
		}
		i++;
	}
	to_return[x] = 0;
	return (to_return);
}

void	read_export(char **env)
{
	int		i;
	char	**var;
	char	*value;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		var = ft_split(env[i], '=');
		if (var[1])
			value = var[1];
		else
			value = "";
		printf("declare -x %s=\"%s\"\n", var[0], value);
		free_that_matrice(var);
		i++;
	}
}

void	read_env(char **env)
{
	unsigned int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		if (find_index(env[i], '=') >= 0)
			printf("%s\n", env[i]);
		i++;
	}
}
