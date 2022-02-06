/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:09:10 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/31 21:11:36 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_shell(void)
{
	char	*shell_path;
	char	*shell;

	shell_path = getenv("SHELL");
	if (shell_path)
		shell = ft_strtrim(shell_path, "/bin/");
	else
		shell = ft_strdup("");
	return (shell);
}

static void		p_err(char *value, char	*shell, char *message)
{
	if (shell && ft_strcmp(shell, "") != 0)
	{
		write(STDERR_FILENO, shell, ft_strlen(shell));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, ": ", 2);
}

void	print_error(int code, char *value)
{
	char	*shell;

	shell = get_shell();
	if (code == 0)
	{
		g_exit_status = 127;
		p_err(value, shell, "command not found\n");
	}
	if (code == 1)
	{
		g_exit_status = 1;
		p_err(value, shell, "too many arguments\n");
	}
	if (code == 2)
	{
		g_exit_status = 1;
		p_err(value, shell, "numeric argument required\n");
	}
	free(shell);
}
