/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:33:12 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/21 19:33:17 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_quoted(char *line)
{
	int i;

	i = 0;
	if (line[i] == '\'')
	{
		i++;
		while (line[i] && line[i] != '\'')
			i++;
	}
	else if (line[i] == '\"')
	{
		i++;
		while (line[i] && line[i] != '\"')
			i++;
	}
	return (i);
}

static int	get_linelen(char *line)
{
	int i;

	i = 0;
	if (get_operator(line))
		return (get_operator(line));
	else
	{
		while (line[i])
		{
			if (line[i] == '\'' || line[i] == '\"')
				i += count_quoted(line + i) + 1;
			while (line[i] && !get_operator(line + i) 
					&& !(line[i] == '\'' || line[i] == '\"'))
				i++;
			if (get_operator(line + i))
				return (i);
		}
		return (i);
	}
}

static void	replace_single_tilda(char **ret, char **env, int j)
{
	free(ret[j]);
	ret[j] = get_bash_var("$HOME", env);
}

char	**copy_n_extract(char **extended, int newtab_size, char **env)
{
	char	**ret;
	char	*ptr;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char *) * (newtab_size + 1));
	while (extended[i])
	{
		ptr = extended[i];
		while (*ptr)
		{
			len = get_linelen(ptr);
			ret[j] = ft_strndup(ptr, len);
			if (len == 1 && *ptr == '~')
				replace_single_tilda(ret, env, j);
			ptr += len;
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}
