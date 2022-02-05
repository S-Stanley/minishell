/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/02/04 01:40:44 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				g_exit_status;

void	parse_errors(char **output)
{
	free_that_matrice(output);
	printf("wrong input\n");
}

void	run_minishell(char **environnement, t_history *history)
{
	char		**output;
	char		*command_line;

	command_line = NULL;
	while (1)
	{
		command_line = readline("minishell> ");
		init_signal();
		if (!command_line)
			break ;
		output = ft_extract_operators(ft_extend_vars(
					ft_split_input(command_line), environnement),
				environnement);
		if (!check_input(command_line))
			parse_errors(output);
		else
		{
			exec(output, &environnement, history);
			free_that_matrice(output);
		}
		add_history(command_line);
		free(command_line);
		command_line = NULL;
		unlink("/tmp/.listen-stdin");
	}
}

int	main(int ac, char **av, char **env)
{
	char		**environnement;
	t_history	*history;

	(void)av;
	if (ac != 1)
		return (0);
	history = NULL;
	g_exit_status = 0;
	environnement = get_env(env);
	init_signal();
	if (!isatty(STDIN_FILENO))
		return (0);
	run_minishell(environnement, history);
	unlink("/tmp/.listen-stdin");
	free_that_matrice(environnement);
	free_history(history);
	rl_clear_history();
	close_fds();
	return (0);
}
