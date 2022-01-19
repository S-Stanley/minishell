/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:13:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/18 01:35:57 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd_arr(char **cmd, int x, char *output, int *exit_status)
{
	if (x == 0)
	{
		cmd[x] = get_full_path(output);
		if (!cmd[x])
		{
			print_error(COMMAND_NOT_FOUND, output, exit_status);
			return (NULL);
		}
	}
	else
		cmd[x] = output;
	return (cmd[x]);
}
