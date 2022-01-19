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
	char		**expanded;//
	int			i;

	(void)av;
	(void)ac;

	input_example = "echo $HOME \"hello      there\" how are 'you 'doing? $USER |wc -l >outfile";
	expanded = ft_split_input(input_example);
	ft_extend_vars(expanded, env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		fflush(stdout);
		i++;
	}
	free_that_matrice(expanded);
	input_example = " $USER \"$USER\" '$USER' zz$USER 'zz$USER' \"zz$USER\" ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = " $USERff \"$USERff\" '$USERff' zz$USERff 'zz$USERff' \"zz$USERff\" ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "12$USER34 \"12$USER34\" '12$USER34' ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "12$USER34$HOME56 \"12$USER34$HOME56\" '12$USER34$HOME56' ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "12$USER 34$HOME 56 \"12$USER 34$HOME 56\" '12$USER 34$HOME 56' ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = " $USER ff \"$USER ff\" '$USER ff' zz $USER ff 'zz $USER ff' \"zz $USER ff\" ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "12$3USER4 \"12$3USER4\" '12$3USER4'";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "12$U3SER4$HOME56 \"12$U3SER4$HOME56\" '12$U3SER4$HOME56' ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "12$U3SER4$H5OME6 \"12$U3SER4$H5OME6\" '12$U3SER4$H5OME6' ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "12$USER-34$H5OME6 \"12$USER-34$H5OME6\" '12$USER-34$H5OME6' ";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "\"\"\"\"";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);
	input_example = "\'\'\'\'";
	expanded = ft_extend_vars(ft_split_input(input_example), env);
	i = 0;
	printf("input = %s\n", input_example);
	while (expanded[i])
	{
		printf("s:\t%s\n", expanded[i]);
		i++;
	}
	free_that_matrice(expanded);

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

