/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/17 21:16:31 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_len_matrice(char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return (0);
	while (matrice[i])
		i++;
	return (i);
}

int	count_next_stop(char **output, int i)
{
	int		count;

	count = 0;
	while (i < ft_len_matrice(output) && ft_strcmp(output[i], "|") != 0)
	{
		count++;
		i++;
	}
	return (count + 1);
}

char	*get_full_path(char *cmd)
{
	char	**path;
	int		i;
	char	*full_path;
	char	*path_with_slash;
	char	*path_env;

	i = 0;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path = ft_split(path_env, ':');
	while (path[i])
	{
		path_with_slash = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(full_path, X_OK) == 0)
		{
			free_that_matrice(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_that_matrice(path);
	return (NULL);
}

void	parse_and_exec(char	**output, char **env)
{
	t_token	*lst;
	int		i;
	char	**cmd;
	int		x;

	(void)env;
	lst = NULL;
	i = 0;
	while (i < ft_len_matrice(output))
	{
		x = 0;
		cmd = malloc(sizeof(char *) * count_next_stop(output, i));
		if (!cmd)
			return ;
		while (output[i] && ft_strcmp(output[i], "|") != 0)
		{
			if (x == 0)
				cmd[x] = get_full_path(output[i]);
			else
				cmd[x] = output[i];
			i++;
			x++;
		}
		cmd[x] = NULL;
		get_full_path(cmd[0]);
		lst = add_token(lst, 0, 1, cmd);
		i++;
	}
	exec_cmd(lst, env);
	free_that_matrice(output);
	free_token_list(lst);
}

int	main(int ac, char **av, char **env)
{
	char		**output;
	char		*command_line;

	(void)ac;
	(void)av;
	while (1)
	{
		command_line = readline("> ");
		add_history(command_line);
		output = ft_split_input(command_line);
		parse_and_exec(output, env);
	}
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

