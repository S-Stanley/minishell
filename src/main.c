/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/29 17:00:18 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				g_exit_status;

void	exit_handler(int nb)
{
	if (nb == 3)
		return ;
	// rl_replace_line("", 0);
	// rl_redisplay();
	printf("\n");
	get_prompt();
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
	signal(SIGINT, exit_handler);
	signal(SIGQUIT, exit_handler);
	while (1)
	{
		if (!isatty(STDIN_FILENO))
			break ;
		get_prompt();
		command_line = readline("");
		history = add_cmd_line(history, command_line);
		if (!command_line)
			break ;
		add_history(command_line);
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
			exec(output, &environnement, history);
			free_that_matrice(output);
		}
	}
	// rl_clear_history();
	free_that_matrice(environnement);
	free_history(history);
	return (0);
}
