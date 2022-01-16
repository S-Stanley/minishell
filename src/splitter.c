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

#include <minishell.h>

static int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 12))
		return (1);
	return (0);
}

static void	check_handle_quotes(int *sin_q, int *doub_q, char c)
{
	if (c == '\'' && !(*sin_q))
		*sin_q = 1;
	else if (c == '\'' && *sin_q)
		*sin_q = 0;
	else if (c == '\"' && !(*doub_q))
		*doub_q = 1;
	else if (c == '\"' && *doub_q)
		*doub_q = 0;
}

static int	wcount(char *s)
{
	int	w;
	int	in_sin_q;
	int	in_doub_q;

	w = 0;
	in_sin_q = 0;
	in_doub_q = 0;
	while (*s)
	{
		while (*s && is_whitespace(*s))
			s++;
		if (*s && !is_whitespace(*s))
		{
			w++;
			check_handle_quotes(&in_sin_q, &in_doub_q, *s);
			while (*s && (!is_whitespace(*s) || in_sin_q || in_doub_q))
			{
				check_handle_quotes(&in_sin_q, &in_doub_q, *s);
				s++;
			}
		}
	}
	return (w);
}

// static char	*allocate(char *s)
// {
// 	char	*word;
// 	int		chars;

// 	chars = 0;
// 	while (s[chars] && !is_whitespace(s[chars]))
// 		chars++;
// 	word = malloc(sizeof(char) * (chars + 1));
// 	if (!word)
// 		return (NULL);
// 	word[chars--] = '\0';
// 	while (chars >= 0)
// 	{
// 		word[chars] = s[chars];
// 		chars--;
// 	}
// 	return (word);
// }

char	**split_spaces(char *st)
{
	// char	**table;
	int		wc;
	// int		i;

	// i = 0;
	(void)st;
	wc = wcount(st);
	printf("%d\n", wc);
	// table = malloc(sizeof(char *) * (wc + 1));
	// if (table)
	// {
	// 	while (*st && i < wc)
	// 	{
	// 		while (*st && is_whitespace(*st))
	// 			st++;
	// 		if (*st && !is_whitespace(*st))
	// 		{
	// 			table[i++] = allocate(st);
	// 			while (*st && !is_whitespace(*st))
	// 				st++;
	// 		}
	// 	}
	// 	table[i] = NULL;
	// }
	// return (table);
	return NULL;
}

char	**ft_split_input(char *str)
{
	char	**splitted;

	splitted = split_spaces(str);

	return (splitted);
}
