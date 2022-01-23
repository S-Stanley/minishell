/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/23 16:52:54 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	g_exit_status;

void	exit_handler(int nb)
{
	(void)nb;
	close(0);
	close(1);
	close(2);
	exit(0);
}

typedef struct s_history {
	char				*str;
	struct s_history	*next;
}	t_history;

t_history	*create_new_history(char *to_add)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	if (!new)
		return (NULL);
	new->str = to_add;
	new->next = NULL;
	return (new);
}

t_history	*add_cmd_line(t_history *cmd, char *to_add)
{
	t_history	*new;
	t_history	*tmp;

	new = create_new_history(to_add);
	if (!new)
		return (cmd);
	if (!cmd)
		return (new);
	tmp = cmd;
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = new;
	return (tmp);
}

void	free_history(t_history *history)
{
	t_history	*tmp;

	while (history)
	{
		tmp = history->next;
		free(history->str);
		free(history);
		history = tmp;
	}
}

int	main(int ac, char **av, char **env)
{
	char		**output;
	char		*command_line;
	char		*prompt;
	char		**environnement;
	t_history	*history;

	(void)av;
	if (ac != 1)
		return (0);
	history = NULL;
	g_exit_status = 0;
	environnement = get_env(env);
	signal(SIGINT, exit_handler);
	while (1)
	{
		prompt = get_prompt();
		command_line = readline(prompt);
		history = add_cmd_line(history, command_line);
		free(prompt);
		if (!command_line)
			break ;
		add_history(command_line);
		output = ft_extract_operators(ft_extend_vars(ft_split_input(command_line), env));
		exec(output, &environnement);
		free_that_matrice(output);
	}
	free_history(history);
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
