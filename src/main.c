/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/30 17:49:19 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				g_exit_status;

void	exit_handler(int nb)
{
	if (nb == 3)
		return ;
	//rl_replace_line("", 0);
	printf("\n");
	printf("minishell> ");
	rl_redisplay();
}

t_history	*update_history(char *command_line, t_history *history)
{
	add_history(command_line);
	history = add_cmd_line(history, command_line);
	return (history);
}

int	main(int ac, char **av, char **env)
{
	char		**output;
	char		*command_line;
	char		**environnement;
	t_history	*history;

	(void)av;
	if (ac != 1)
		return (0);
	history = NULL;
	g_exit_status = 0;
	environnement = get_env(env);
	command_line = NULL;
	signal(SIGINT, exit_handler);
	signal(SIGQUIT, exit_handler);
	while (1)
	{
		if (!isatty(STDIN_FILENO))
			break ;
		// get_prompt();
		if (command_line)
			free(command_line);
		command_line = readline("minishell> ");
		if (!command_line)
			break ;
		output = ft_extract_operators(ft_extend_vars(
					ft_split_input(command_line), environnement),
				environnement);
		// check errors in prompt
		if (!check_input(command_line))
		{
			free_that_matrice(output);
			printf("wrong input\n");
		}
		else
		{
			history = update_history(ft_strdup(command_line), history);
			exec(output, &environnement, history);
			free_that_matrice(output);
		}
		free(command_line);
		command_line = NULL;
	}
	// rl_clear_history();
	free_that_matrice(environnement);
	free_history(history);
	return (0);
}
