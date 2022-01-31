/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:34:00 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 20:09:39 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

bool	check_var_exist(char **cmd, char **env)
{
	char	*find;

	if (!cmd || !env)
		return (env);
	find = get_bash_var(cmd[1], env);
	if (ft_strcmp(find, "") == 0)
	{
		free(find);
		return (false);
	}
	free(find);
	return (true);
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
