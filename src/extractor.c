/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:49:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/02/03 03:13:59 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_operator(char *s)
{
	if (*s == '|')
		return (1);
	if (*s == '>')
	{
		s++;
		if (*s == '>')
			return (2);
		return (1);
	}
	if (*s == '<')
	{
		s++;
		if (*s == '<')
			return (2);
		return (1);
	}
	return (0);
}

static void	skip_to_next_quote(int *j, int *chars_per_line, char *line)
{
	if (line[*j] == '\"')
	{
		(*j)++;
		while (line[*j] && line[*j] != '\"')
			(*j)++;
	}
	else if (line[*j] == '\'')
	{
		(*j)++;
		while (line[*j] && line[*j] != '\'')
			(*j)++;
	}
	if (!line[*j])
		(*chars_per_line)++;
	else
	{
		(*j)++;
		if (!line[*j] || get_operator(line + *j))
			(*chars_per_line)++;
	}
}

static void	count_sublines(char *line, int *ops_per_line, int *chars_per_line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (get_operator(line + j))
		{
			(*ops_per_line)++;
			j += get_operator(line + j);
		}
		else if (line[j] == '\'' || line[j] == '\"')
			skip_to_next_quote(&j, chars_per_line, line);
		else
		{
			while (line[j] && !get_operator(line + j)
				&& !(line[j] == '\'' || line[j] == '\"'))
				j++;
			if (!line[j] || get_operator(line + j))
				(*chars_per_line)++;
		}
	}
}

static int	count_new_tab_size(char **extended)
{
	int		i;
	int		ops_per_line;
	int		chars_per_line;
	int		res;

	res = 0;
	i = 0;
	while (extended[i])
	{
		ops_per_line = 0;
		chars_per_line = 0;
		count_sublines(extended[i], &ops_per_line, &chars_per_line);
		res += ops_per_line + chars_per_line;
		i++;
	}
	return (res);
}

char	**ft_extr_ops(char **extended, char **env)
{
	int		new_len;
	int		old_len;
	char	**ret;

	old_len = 0;
	ret = NULL;
	while (extended[old_len])
		old_len++;
	new_len = count_new_tab_size(extended);
	if (old_len == new_len)
		return (extended);
	ret = copy_n_extract(extended, new_len, env);
	free_that_matrice(extended);
	return (ret);
}
