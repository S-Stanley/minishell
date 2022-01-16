/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coop <coop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 09:41:57 by rokupin           #+#    #+#             */
/*   Updated: 2021/08/02 01:05:05 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	wcount(char *s, char c)
{
	int	w;

	w = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			w++;
			while (*s && *s != c)
				s++;
		}
	}
	return (w);
}

static char	*allocate(char *s, char c)
{
	char	*word;
	int		chars;

	chars = 0;
	while (s[chars] && s[chars] != c)
		chars++;
	word = malloc(sizeof(char) * (chars + 1));
	if (!word)
		return (NULL);
	word[chars--] = '\0';
	while (chars >= 0)
	{
		word[chars] = s[chars];
		chars--;
	}
	return (word);
}

static char	**split(char const *s, char c)
{
	char	**table;
	char	*st;
	int		wc;
	int		i;

	st = (char *)s;
	i = 0;
	wc = wcount(st, c);
	table = malloc(sizeof(char *) * (wc + 1));
	if (table)
	{
		while (*st && i < wc)
		{
			while (*st && *st == c)
				st++;
			if (*st && *st != c)
			{
				table[i++] = allocate(st, c);
				while (*st && *st != c)
					st++;
			}
		}
		table[i] = NULL;
	}
	return (table);
}

char	**ft_split(char const *s, char c)
{
	if (s)
		return (split(s, c));
	return (NULL);
}
