/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:09:10 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 10:42:59 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(int code, char *value)
{
	char	*shell_path;
	char	*shell;

	shell_path = getenv("SHELL");
	if (shell_path)
		shell = ft_strtrim(shell_path, "/bin/");
	else
		shell = ft_strdup("");
	if (code == 0)
	{
		g_exit_status = 127;
		printf("%s: %s: command not found\n", shell, value);
	}
	free(shell);
}
