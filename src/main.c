/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/23 17:13:16 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	g_exit_status;

void	exit_handler(int nb)
{
	(void)nb;
	close(0);
	close(1);
	close(2);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	char		**output;
	char		*command_line;
	char		*prompt;
	char		**environnement;
	t_history	*history;

	(void)av;
	if (ac != 1)
		return (0);
	history = NULL;
	g_exit_status = 0;
	environnement = get_env(env);
	signal(SIGINT, exit_handler);
	while (1)
	{
		prompt = get_prompt();
		command_line = readline(prompt);
		history = add_cmd_line(history, command_line);
		free(prompt);
		if (!command_line)
			break ;
		add_history(command_line);
		output = ft_extract_operators(ft_extend_vars(ft_split_input(command_line), env));
		exec(output, &environnement);
		free_that_matrice(output);
	}
	free_that_matrice(environnement);
	free_history(history);
	return (0);
}
