/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:11:38 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 02:13:40 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_cmd_in_path(char **path, char *cmd)
{
	int		i;
	char	*full_path;
	char	*path_with_slash;

	i = 0;
	if (is_builtin(cmd))
		return (cmd);
	while (path[i])
	{
		path_with_slash = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	print_error(0, cmd);
	if (!cmd)
		return (NULL);
	return (ft_strdup(cmd));
}

int	find_index(const char *str, char c)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_full_path(char *cmd, char **env)
{
	char	**path;
	char	*path_env;
	char	*res;

	if (find_index(cmd, '/') != -1)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	path_env = get_bash_var("PATH", env);
	if (!path_env)
		return (NULL);
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	res = find_cmd_in_path(path, cmd);
	free(path_env);
	if (res)
	{
		free_that_matrice(path);
		return (res);
	}
	free_that_matrice(path);
	return (NULL);
}

char	**full_cmd(char **str)
{
	char	**to_return;
	char	**to_split;

	to_split = get_splitter();
	to_return = ft_matrice_split(str, to_split);
	free(to_split);
	if (to_return[0] == 0 || to_return[0][0] == 0)
	{
		free_that_matrice(to_return);
		return (NULL);
	}
	return (to_return);
}
