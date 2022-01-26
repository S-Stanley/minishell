/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:30:36 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/26 20:33:34 by sserbin          ###   ########.fr       */
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

bool	builtin_echo(char **cmd)
{
	unsigned int	i;
	unsigned int	x;

	i = 1;
	if (!cmd || count_len_matrice(cmd) == 1)
		return (true);
	while (cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		x = 0;
		while (cmd[i][x] == 'n')
			x++;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (should_print_nl(cmd))
		printf("\n");
	return (true);
}
