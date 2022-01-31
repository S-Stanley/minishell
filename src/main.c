/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/31 02:37:33 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				g_exit_status;

void	exit_handler(int nb)
{
	if (nb == 3)
		return ;
	g_exit_status = 130;
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\n");
	printf("minishell> ");
}

t_history	*update_history(char *command_line, t_history *history)
{
	add_history(command_line);
	history = add_cmd_line(history, command_line);
	return (history);
}

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
		if (!command_line)
			break ;
		output = ft_extract_operators(ft_extend_vars(
					ft_split_input(command_line), environnement),
				environnement);
		if (!check_input(command_line))
			parse_errors(output);
		else
		{
			history = update_history(ft_strdup(command_line), history);
			exec(output, &environnement, history);
			free_that_matrice(output);
		}
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
	signal(SIGINT, exit_handler);
	signal(SIGQUIT, exit_handler);
	if (!isatty(STDIN_FILENO))
		return (0);
	run_minishell(environnement, history);
	unlink("/tmp/.listen-stdin");
	free_that_matrice(environnement);
	free_history(history);
	return (0);
}
