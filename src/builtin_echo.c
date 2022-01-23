/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:30:36 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 11:38:02 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	builtin_echo(char **cmd)
{
	unsigned int	i;

	i = 1;
	if (!cmd || count_len_matrice(cmd) == 1)
		return (true);
	if (cmd[i][0] == '-')
		i++;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
	}
	if (cmd[1][0] != '-' || cmd[1][1] != 'n')
		printf("\n");
	return (true);
}
