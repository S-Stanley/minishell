/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 04:11:46 by rokupin           #+#    #+#             */
/*   Updated: 2022/02/08 20:08:57 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_arrow(char *command_line, int *i, char arrow)
{
	(*i)++;
	if (command_line[*i] == arrow)
		(*i)++;
	while (command_line[*i] && command_line[*i] != '>'
		&& command_line[*i] != '<' && command_line[*i] != '|')
	{
		if (command_line[*i] > ' ' && command_line[*i] <= '~')
			return (1);
		(*i)++;
	}
	return (0);
}

static int	check_pipe(char *command_line, int *i)
{
	(*i)++;
	while (command_line[*i] && command_line[*i] != '>'
		&& command_line[*i] != '<' && command_line[*i] != '|')
	{
		if (command_line[*i] > ' ' && command_line[*i] <= '~')
			return (1);
		(*i)++;
	}
	return (0);
}

static int	check_signs(char *command_line, int *i, int j)
{
	if (command_line[*i] == '\'' || command_line[*i] == '\"')
	{
		(*i)++;
		while (command_line[*i] && command_line[*i] != command_line[j])
			(*i)++;
		if (command_line[*i] == command_line[j])
		{
			(*i)++;
			return (1);
		}
		return (0);
	}
	else if (command_line[*i] == '>' || command_line[*i] == '<')
	{
		if (!check_arrow(command_line, i, command_line[*i]))
			return (0);
	}
	else if (command_line[*i] == '|')
	{
		if (!check_pipe(command_line, i))
			return (0);
	}
	return (1);
}

int	check_input(char *input)
{
	int		i;
	int		unq_len;
	char	*unq_inp;

	i = 0;
	unq_len = get_unquoted_len(input);
	if ((size_t)unq_len != ft_strlen(input))
	{
		unq_inp = q_remove(input, unq_len);
		if (unq_inp[0] == '|' || unq_inp[ft_strlen(unq_inp)] == '|')
		{
			free(unq_inp);
			return (0);
		}
		free(unq_inp);
	}
	while (input[i])
	{
		while (input[i] && input[i] != '>'
			&& input[i] != '<' && input[i] != '|'
			&& input[i] != '\'' && input[i] != '\"')
			i++;
		if (!check_signs(input, &i, i))
			return (0);
	}
	return (1);
}
