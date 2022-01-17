/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/16 21:24:49 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <minishell.h>
#include "../include/minishell.h"

// main to test string_splitter
int	main(int ac, char **av, char **env)
{
	//char		*command_line;
	//t_prompt	prompt;
	
	char		*input_example;//
	char		**output_example;//
	int i = 0;

	(void)env;
	(void)ac;
	(void)av;

	input_example = "echo \"hello      there\" how are 'you 'doing? $USER |wc -l >outfile";
	output_example = ft_split_input(input_example);
	while (output_example[i])
	{
		printf("%s\n", output_example[i]);
		i++;
	}


	// prompt.first_token = NULL;
	// prompt.env = env;
	// prompt.token_len = 0;
	// prompt.line = NULL;
	// while (1)
	// {
	// 	command_line = readline("> ");
	// 	add_history(command_line);
	// }
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

