/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:37:29 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/07 20:04:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**return_env_and_free(char **env,
	char **env_var_split, char **to_add_split)
{
	clean_two_matrice(env_var_split, to_add_split);
	return (env);
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
				return (return_env_and_free(env, env_var_split, to_add_split));
			free(env[i]);
			env[i] = ft_strdup(to_add);
			clean_two_matrice(env_var_split, to_add_split);
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
	free(env);
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

char	**remove_item_env(char **cmd, char **env)
{
	int		i;
	char	**to_return;
	int		x;

	if (!check_var_exist(cmd, env))
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
