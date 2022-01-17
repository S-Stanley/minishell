/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/18 00:46:35 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(int code, char *value, char **env)
{
	char	*shell_path;
	char	*shell;

	shell_path = get_bash_var("$SHELL", env);
	if (shell_path)
		shell = ft_strtrim(shell_path, "/bin/");
	else
		shell = ft_strdup("");
	if (code == 0)
		printf("%s: %s: command not found\n", shell, value);
	free(shell_path);
	free(shell);
}

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

char	*find_cmd_in_path(char **path, char *cmd)
{
	int		i;
	char	*full_path;
	char	*path_with_slash;

	i = 0;
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
	return (NULL);
}

char	*get_full_path(char *cmd)
{
	char	**path;
	char	*path_env;
	char	*res;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	res = find_cmd_in_path(path, cmd);
	if (res)
		return (res);
	free_that_matrice(path);
	return (NULL);
}

t_token	*build_lst(char	**output, char **env, int *exit_status)
{
	t_token	*lst;
	int		i;
	int		x;
	char	**cmd;

	i = 0;
	lst = NULL;
	while (i < ft_len_matrice(output))
	{
		x = 0;
		cmd = malloc(sizeof(char *) * count_next_stop(output, i));
		if (!cmd)
		{
			free_that_matrice(output);
			free_token_list(lst);
			return (NULL);
		}
		while (output[i] && ft_strcmp(output[i], "|") != 0)
		{
			if (x == 0)
			{
				cmd[x] = get_full_path(output[i]);
				if (!cmd[x])
				{
					print_error(COMMAND_NOT_FOUND, output[i], env);
					exit_status[0] = 127;
					free_that_matrice(output);
					free_token_list(lst);
					return (NULL);
				}
			}
			else
				cmd[x] = output[i];
			i++;
			x++;
		}
		cmd[x] = NULL;
		lst = add_token(lst, 0, 1, cmd);
		i++;
	}
	return (lst);
}

void	parse_and_exec(char	**output, char **env, int *exit_status)
{
	t_token	*lst;

	(void)env;
	lst = NULL;
	lst = build_lst(output, env, exit_status);
	exec_cmd(lst, env);
	free_that_matrice(output);
	free_token_list(lst);
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
	exit_status[0] = 0;
	while (1)
	{
		command_line = readline("> ");
		add_history(command_line);
		output = ft_split_input(command_line);
		parse_and_exec(output, env, exit_status);
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

