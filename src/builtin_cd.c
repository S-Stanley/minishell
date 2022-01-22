/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:47:48 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/22 18:13:48 by sserbin          ###   ########.fr       */
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

char	*get_backward_path(char *cwd)
{
	int		size;
	char	*full_path;

	size = find_last_index(cwd, '/') + 1;
	full_path = malloc(sizeof(char) * size);
	ft_strlcpy(full_path, cwd, size);
	return (full_path);
}

char	*get_forward_path(char *cwd, char *path)
{
	char	*cwd_with_slash;
	char	*full_path;

	cwd_with_slash = ft_strjoin(cwd, "/");
	full_path = ft_strjoin(cwd_with_slash, path);
	free(cwd_with_slash);
	return (full_path);
}

bool	builtin_cd(char *path)
{
	char	*full_path;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, -1);
	if (ft_strcmp(path, "..") == 0 || ft_strcmp(path, "-") == 0)
		full_path = get_backward_path(cwd);
	else if (find_index(path, '/') == 0)
		full_path = path;
	else
		full_path = get_forward_path(cwd, path);
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
