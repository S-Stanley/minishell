/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/16 18:35:23 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*command_line;
	t_prompt	prompt;

	(void)ac;
	(void)av;
	prompt.first_token = NULL;
	prompt.env = env;
	prompt.token_len = 0;
	prompt.line = NULL;
	while (1)
	{
		command_line = readline("> ");
		add_history(command_line);
	}
	return (0);
}

/*

char *exec = "ls";
char **arg = {"-l", 0}

// check if it's a built in
char *full_path = get_full_path(exec); // return /bin/ls
if (full_path)
	char **cmd = {full_path, "-l", 0}
execve(cmd[0], cmd, env);

*/
