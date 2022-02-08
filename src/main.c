/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/02/08 21:10:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				g_exit_status;

void	parse_errors(char **output)
{
	free_that_matrice(output);
	write(STDERR_FILENO, "minishell: wrong input!\n", 24);
	g_exit_status = 2;
}

void	run_minishell(char **env, t_history *history)
{
	char		**output;
	char		*comm;

	comm = NULL;
	while (1)
	{
		comm = readline("minishell> ");
		if (ft_strlen(comm) == 0)
			continue ;
		init_signal();
		if (!comm)
			break ;
		output = ft_extr_ops(ft_extend_vars(ft_split_input(comm), env), env);
		if (!check_input(comm))
			parse_errors(output);
		else if (output && *output && *comm && ft_strcmp(comm, "\n"))
		{
			exec(output, &env, history);
			free_that_matrice(output);
		}
		add_history(comm);
		free(comm);
		comm = NULL;
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
