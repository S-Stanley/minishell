/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:17:24 by rokupin           #+#    #+#             */
/*   Updated: 2022/02/03 02:17:54 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	copy_inside_quotes(int *i, int *j, char *str, char *new)
{
	char	q;

	q = str[*i];
	(*i)++;
	while (str[*i] != q)
	{
		new[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	(*i)++;
}

char	*q_remove(char *str, int len)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			copy_inside_quotes(&i, &j, str, new);
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

int	get_unquoted_len(char *str)
{
	int		i;
	int		newlen;
	char	q;

	i = 0;
	newlen = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			q = str[i];
			i++;
			while (str[i] != q)
			{
				newlen++;
				i++;
			}
		}
		else
			newlen++;
		i++;
	}
	return (newlen);
}

char	**unquote(char **splitted)
{
	int		i;
	int		newlen;
	char	*unquoted;

	if (!splitted || !(*splitted))
		return (NULL);
	i = 0;
	while (splitted[i])
	{
		newlen = get_unquoted_len(splitted[i]);
		if ((size_t)newlen != ft_strlen(splitted[i]))
		{
			unquoted = q_remove(splitted[i], newlen);
			splitted[i] = unquoted;
		}
		i++;
	}
	return (splitted);
}
