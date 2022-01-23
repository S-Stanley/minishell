/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:30:36 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 11:52:59 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	should_print_bn(char **cmd)
{
	int		i;

	i = 1;
	if (cmd[1][0] == '-')
	{
		while (cmd[1][i])
		{
			if (cmd[1][i] != 'n')
			{
				printf("\n");
				return ;
			}
			i++;
		}
		return ;
	}
	printf("\n");
}

bool	builtin_echo(char **cmd)
{
	unsigned int	i;
	unsigned int	x;

	i = 1;
	if (!cmd || count_len_matrice(cmd) == 1)
		return (true);
	x = 1;
	if (cmd[i][0] == '-')
	{
		while (cmd[i][x] == 'n')
		{
			x++;
		}
		if (!cmd[i][x])
			i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	should_print_bn(cmd);
	return (true);
}
