/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:47:48 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/22 17:58:07 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_last_index(char *str, char to_find)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	if (!str)
		return (index);
	while (str[i])
	{
		if (str[i] == to_find)
			index = i;
		i++;
	}
	return (index);
}

bool	builtin_cd(char *path)
{
	char	*full_path;
	int		size;
	char	*cwd;
	char	*cwd_with_slash;

	cwd = NULL;
	cwd = getcwd(cwd, -1);
	if (ft_strcmp(path, "..") == 0 || ft_strcmp(path, "-") == 0)
	{
		size = find_last_index(cwd, '/') + 1;
		full_path = malloc(sizeof(char) * size);
		ft_strlcpy(full_path, cwd, size);
	}
	else if (find_index(path, '/') == 0)
		full_path = path;
	else
	{
		cwd_with_slash = ft_strjoin(cwd, "/");
		full_path = ft_strjoin(cwd_with_slash, path);
		free(cwd_with_slash);
	}
	free(cwd);
	if (chdir(full_path) == 0)
	{
		if (find_index(path, '/') != 0)
			free(full_path);
		return (true);
	}
	return (false);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, -1);
	prompt = ft_strjoin(cwd, "> ");
	return (prompt);
}
