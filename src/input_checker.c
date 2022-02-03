/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 04:11:46 by rokupin           #+#    #+#             */
/*   Updated: 2022/02/03 03:14:45 by roman            ###   ########.fr       */
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

int	check_input(char *command_line)
{
	int	i;

	i = 0;
	if (command_line[0] == '|'
		|| command_line[ft_strlen(command_line)] == '|')
		return (0);
	while (command_line[i])
	{
		while (command_line[i] && command_line[i] != '>'
			&& command_line[i] != '<' && command_line[i] != '|'
			&& command_line[i] != '\'' && command_line[i] != '\"')
				i++;
		if (!check_signs(command_line, &i, i))
			return (0);
	}
	return (1);
}
