/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/21 20:59:14 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

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
	int			*exit_status;

	(void)av;
	if (ac != 1)
		return (0);
	exit_status = malloc(sizeof(int));
	if (!exit_status)
		return (0);
	signal(SIGINT, exit_handler);
	while (1)
	{
		exit_status[0] = 0;
		command_line = readline("> ");
		if (!command_line)
		{
			write(1, "test\n", 5);
			exit (0);
		}
		add_history(command_line);
		output = ft_split_input(command_line);
		if (ft_len_matrice(output) == 1 && ft_strcmp(output[0], "exit") == 0)
			break ;
		exec(output, env, exit_status);
	}
	free(exit_status);
	return (0);
}

//	Original main() function
//int	main(int ac, char **av, char **env)
//{
//	char		*command_line;
//	t_prompt	prompt;
//
//	(void)env;
//	(void)ac;
//	(void)av;
//
//	prompt.first_token = NULL;
//	prompt.env = env;
//	prompt.token_len = 0;
//	prompt.line = NULL;
//	while (1)
//	{
//		command_line = readline("> ");
//		add_history(command_line);
//	}
//	return (0);
//}

//===================================
// Some tests
//	
//	input_example = "echo \"hello   '   there\" how are you 'doing? $USER |wc -l >outfile";
//	output_example = ft_split_input(input_example);
//	if (output_example == NULL)
//		printf("wrong quote placing!\n");
//
//	
//	input_example = "echo '\"hello   '   there\" how are 'you 'doing? $USER |wc -l >outfile";
//	output_example = ft_split_input(input_example);
//	if (output_example == NULL)
//		printf("wrong quote placing!\n");
//
//

//==================================
// Just notes!
//=====================================

/*
char *exec = "ls";
char **arg = {"-l", 0}

// check if it's a built in
char *full_path = get_full_path(exec); // return /bin/ls
if (full_path)
	char **cmd = {full_path, "-l", 0}
execve(cmd[0], cmd, env);

*/
