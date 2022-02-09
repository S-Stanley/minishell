/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:30:36 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/09 15:12:49 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	should_print_nl(char **cmd)
{
	unsigned int	i;
	unsigned int	x;

	if (count_len_matrice(cmd) < 2)
		return (true);
	i = 1;
	if (cmd[i][0] != '-')
		return (true);
	x = 1;
	while (cmd[i])
	{
		if (i == 2)
			break ;
		while (cmd[i][x])
		{
			if (cmd[i][x] == 'n')
				x++;
			else
				return (true);
		}
		i++;
	}
	return (false);
}

bool	print_nl(char **cmd)
{
	if (should_print_nl(cmd))
		printf("\n");
	return (true);
}

int	start_to_write_at(unsigned int i, char **cmd)
{
	unsigned int	x;
	unsigned int	tmp;

	x = 0;
	tmp = i;
	if (cmd[i][x] != '-')
		return (tmp);
	while (cmd[i])
	{
		x = -1;
		if (cmd[i][x + 1] == '-')
			x++;
		else
			return (i);
		while (cmd[i][++x])
			if (cmd[i][x] != 'n' && cmd[i][x] != ' ')
				return (i);
		i++;
	}
	return (i);
}

bool	builtin_echo(char **cmd)
{
	unsigned int	i;

	i = 1;
	if (!cmd)
		return (true);
	if (count_len_matrice(cmd) > 1)
	{
		i = start_to_write_at(i, cmd);
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	return (print_nl(cmd));
}
