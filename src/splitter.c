/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:28:04 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/16 21:36:40 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <minishell.h>
#include "../include/minishell.h"

static int	check_handle_quotes(char **s)
{
	if (*(*s) == '\'')
	{
		(*s)++;
		while (*(*s) && *(*s) != '\'')
			(*s)++;
		if (!*(*s))
			return (1); // particular quote is not closed
	}
	else if (*(*s) == '\"')
	{
		(*s)++;
		while (*(*s) && *(*s) != '\"')
			(*s)++;
		if (!*(*s))
			return (1); // particular quote is not closed
	}
	return (0); // We've hound the closing quote
}

static int	wcount(char *s)
{
	int	w;

	w = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || (*s >= 9 && *s <= 12)))
			s++;
		if (*s && !(*s == ' ' || (*s >= 9 && *s <= 12)))
		{
			w++;
			if (check_handle_quotes(&s))
				return (-1);
			while (*s && !(*s == ' ' || (*s >= 9 && *s <= 12)))
			{
				s++;
				if (check_handle_quotes(&s))
					return (-1);
			}
		}
	}
	return (w);
}

static int	get_word_length(char *s)
{
	int	chars;

	chars = 0;
	while (s[chars] &&
			!(s[chars] == ' ' || (s[chars] >= 9 && s[chars] <= 12)))
	{
		if (s[chars] == '\'')
		{
			chars++;
			while (s[chars] != '\'')
				chars++;
		}
		else if (s[chars] == '\"')
		{
			chars++;
			while (s[chars] != '\"')
				chars++;
		}
		chars++;
	}
	return (chars);
}

static char	*allocate(char **str)
{
 	char	*word;
 	int		chars;
	char	*s;

 	chars = 0;
	s = *str;
	chars = get_word_length(s);
 	word = malloc(sizeof(char) * (chars + 1));
 	if (!word)
 		return (NULL);
	(*str) += chars;
 	word[chars--] = '\0';
 	while (chars >= 0)
 	{
 		word[chars] = s[chars];
 		chars--;
 	}
 	return (word);
}

char	**ft_split_input(char *st)
{
	char	**table;
	int		wc;
	int		i;

	i = 0;
	wc = wcount(st);
	if (wc == -1)
		return (NULL);
	table = malloc(sizeof(char *) * (wc + 1));
	if (table)
	{
		while (*st && i < wc)
		{
			while (*st && (*st == ' ' || (*st >= 9 && *st <= 12)))
				st++;
			if (*st && !(*st == ' ' || (*st >= 9 && *st <= 12)))
				table[i++] = allocate(&st);
		}
		table[i] = NULL;
	}
	return (table);
}
