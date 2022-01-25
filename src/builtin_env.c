/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:37:29 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/26 00:09:36 by sserbin          ###   ########.fr       */
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

bool	is_env_var_exist(char **env, char *to_add)
{
	unsigned int	i;
	char			**to_add_split;
	char			**env_var_split;

	i = 0;
	to_add_split = ft_split(to_add, '=');
	if (!to_add_split)
		return (false);
	while (env[i])
	{
		env_var_split = ft_split(env[i], '=');
		if (ft_strcmp(env_var_split[0], to_add_split[0]) == 0)
		{
			free_that_matrice(env_var_split);
			free_that_matrice(to_add_split);
			return (true);
		}
		free_that_matrice(env_var_split);
		i++;
	}
	free_that_matrice(to_add_split);
	return (false);
}

char	**update_env_var(char **env, char *to_add)
{
	unsigned int	i;
	char			**to_add_split;
	char			**env_var_split;

	i = 0;
	to_add_split = ft_split(to_add, '=');
	if (!to_add_split)
		return (env);
	while (env[i])
	{
		env_var_split = ft_split(env[i], '=');
		if (ft_strcmp(env_var_split[0], to_add_split[0]) == 0)
		{
			if (!to_add_split[1])
				return (env);
			free(env[i]);
			env[i] = ft_strdup(to_add);
			free_that_matrice(env_var_split);
			free_that_matrice(to_add_split);
			return (env);
		}
		free_that_matrice(env_var_split);
		i++;
	}
	free_that_matrice(to_add_split);
	return (env);
}

char	**add_env_var(char **env, char *to_add)
{
	unsigned int	i;
	char			**to_return;

	to_return = malloc(sizeof(char *) * (count_len_matrice(env) + 2));
	if (!to_return)
		return (env);
	i = 0;
	while (env[i])
	{
		to_return[i] = env[i];
		i++;
	}
	to_return[i] = ft_strdup(to_add);
	to_return[++i] = 0;
	return (to_return);
}

char	**update_env(char **cmd, char **env)
{
	unsigned int	i;

	i = 1;
	while (cmd[i])
	{
		if (is_env_var_exist(env, cmd[i]))
			env = update_env_var(env, cmd[i]);
		else
			env = add_env_var(env, cmd[i]);
		i++;
	}
	return (env);
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
	free_that_matrice(env);
	return (to_return);
}

void	read_export(char **env)
{
	int		i;
	char	**var;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		var = ft_split(env[i], '=');
		if (var[1])
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		else
		{
			printf("declare -x %s\n", var[0]);
		}
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
